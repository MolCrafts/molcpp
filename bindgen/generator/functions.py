# -* coding: utf-8 -*
import os
from pycparser import c_ast

from .ctype import Ctype, ArrayType, StringType, PtrToArrayType
from . import MOL_TYPES


class Argument:
    """
    Representing a function argument, or return type
    """

    def __init__(self, name, _type):
        self.name = name
        self.type = _type

    def __str__(self):
        return str(self.name)

    def __repr__(self):
        return repr(self.type) + " " + str(self.name)


class Function:
    """Representing a function, with a name, a return type and some arguments"""

    def __init__(self, name, coord, rettype):
        self.name = name
        self.coord = str(coord)
        self.coord = self.coord.split(os.sep)[-1]
        self.coord = ":".join(self.coord.split(":")[:-1])
        self.args = []
        self.rettype = rettype
        self.is_void_fun = False

    def __str__(self):
        return self.name

    def __repr__(self):
        res = repr(self.rettype)
        res += " " + self.name + "("
        res += ", ".join(map(repr, self.args))
        res += ")"
        return res

    def add_arg(self, arg):
        """Add an argument to the list of arguments"""
        if arg.type.cname == "void" and not arg.type.is_ptr:
            self.is_void_fun = True
        else:
            assert not self.is_void_fun
            self.args.append(arg)

    def args_str(self):
        """Get a comma-separated string containing the argument names"""
        return ", ".join(map(str, self.args))

    @property
    def typename(self):
        """Get the class associated with this function, or None in case of free
        functions."""
        typename = "_".join(self.name.split("_")[:2]).upper()
        if typename in MOL_TYPES:
            return typename
        else:
            return None

    @property
    def member_name(self):
        """
        Get the member part in the name of this function. For example, in
        "chfl_trajectory_topology_set" the member name part is "topology_set"

        In case of default constructor ("chfl_frame" for CHFL_FRAME), returns
        None
        """
        typename = self.typename
        assert typename
        if typename == self.name:
            return None
        else:
            return self.name[len(typename) + 1 :]

    @property
    def is_constructor(self):
        """
        True if this function return a pointer to one of the chemfiles types
        """
        return self.rettype.cname.startswith("CHFL_")


class FunctionVisitor(c_ast.NodeVisitor):
    """AST visitor for C function declaration."""

    def __init__(self, *args, **kwargs):
        super(FunctionVisitor, self).__init__(*args, **kwargs)
        self.functions = []

    def visit(self, *args, **kwargs):
        super(FunctionVisitor, self).visit(*args, **kwargs)
        return self.functions

    def visit_FuncDecl(self, node):
        rettype = type_factory(node.type)
        if hasattr(node.type, "declname"):
            func = Function(node.type.declname, node.coord, rettype)
        else:
            func = Function(node.type.type.declname, node.coord, rettype)

        try:
            parameters = node.children()[0][1].params
        except AttributeError:  # No parameter for this function
            parameters = []

        for parameter in parameters:
            pa_type = type_factory(parameter.type)
            # Hard-coding optional parameters. I do not see how we can guess
            # them from the header only.
            if func.name == "chfl_frame_add_atom" and parameter.name == "velocity":
                pa_type.is_optional = True
            if func.name == "chfl_residue" and parameter.name == "resid":
                pa_type.is_optional = True

            func.add_arg(Argument(parameter.name, pa_type))

        # chfl_warning_callback is a typedef, not a function
        if func.name != "chfl_warning_callback":
            self.functions.append(func)


def type_factory(typ):
    """
    Create a Ctype instance from the pycparser AST
    """
    is_ptr = isinstance(typ, c_ast.PtrDecl)
    if is_ptr:
        if isinstance(typ.type, c_ast.ArrayDecl):
            # Pointer to array
            array_decl = typ.type
            is_const = "const" in array_decl.type.quals
            name = array_decl.type.type.names[0]
            rettype = ArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
            rettype.set_dimensions(-1, array_decl.dim.value)
        elif isinstance(typ.type, c_ast.PtrDecl):
            # Pointer to pointer (to array in chemfiles)
            if isinstance(typ.type.type, c_ast.ArrayDecl):
                array_decl = typ.type.type
                is_const = "const" in array_decl.type.quals
                name = array_decl.type.type.names[0]
                rettype = PtrToArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
                rettype.set_dimensions(-1, array_decl.dim.value)
            else:
                name = typ.type.type.type.names[0]
                assert name in ["chfl_vector3d", "chfl_format_metadata", "char"]
                decl = typ.type
                is_const = "const" in decl.type.quals
                name = decl.type.type.names[0]
                rettype = PtrToArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
                rettype.set_dimensions(-1)
        else:
            # Pointer to anything else
            is_const = "const" in typ.type.quals
            name = typ.type.type.names[0]
            if name == "char":
                rettype = StringType(typ, name, is_ptr=is_ptr, is_const=is_const)
            else:
                rettype = Ctype(typ, name, is_ptr=is_ptr, is_const=is_const)
    else:
        if isinstance(typ, c_ast.ArrayDecl):
            if isinstance(typ.type, c_ast.ArrayDecl):
                # Array of array
                array_decl = typ.type
                is_const = "const" in array_decl.type.quals
                name = array_decl.type.type.names[0]
                rettype = ArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
                rettype.set_dimensions(typ.dim.value, array_decl.dim.value)
            if isinstance(typ.type, c_ast.PtrDecl):
                # Array of pointers
                array_decl = typ.type
                is_const = "const" in array_decl.type.quals
                name = array_decl.type.type.names[0]
                rettype = ArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
                rettype.set_dimensions(-1, -1)
            else:
                # Simple array
                array_decl = typ
                assert not isinstance(array_decl.type, c_ast.ArrayDecl)
                is_const = "const" in array_decl.type.quals
                name = array_decl.type.type.names[0]
                rettype = ArrayType(typ, name, is_ptr=is_ptr, is_const=is_const)
                if hasattr(array_decl.dim, "value"):
                    rettype.set_dimensions(array_decl.dim.value)
                else:
                    rettype.set_dimensions(-1)
        else:
            name = typ.type.names[0]
            is_const = "const" in typ.quals
            rettype = Ctype(typ, name, is_ptr=is_ptr, is_const=is_const)
    return rettype