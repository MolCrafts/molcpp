from pycparser import c_ast

class Ctype(object):
    '''Representing a C type, in a simple way'''

    def __init__(self, type, name, is_ptr=False, is_const=False):
        self.type = type
        self.name = name
        self.is_ptr = is_ptr
        self.is_const = is_const
        self.is_optional = False

    def __str__(self):
        return self.name

    def __repr__(self):
        res = "const " if self.is_const else ""
        res += self.name
        res += "*" if self.is_ptr else ""
        return res
    
class StringType(Ctype):
    '''Representing a C string type'''
    pass

class Enumerator:
    '''A value in a enum'''
    def __init__(self, name, value):
        self.name = name
        self.value = value


class Enum:
    '''Class representing a C enum'''

    def __init__(self, name):
        self.name = name
        self.enumerators = []

    def append(self, name, value=None):
        '''
        Append a name in the enum list, with optional value
        '''
        self.enumerators.append(Enumerator(name, value))

    def __str__(self):
        res = "enum " + self.name + " { \n"
        for enumerator in self.enumerators:
            res += "    " + enumerator.name
            if enumerator.value is not None:
                res += " = " + enumerator.value
            res += "\n"
        res += "}"
        return res

    def __repr__(self):
        return str(self)


ENUM_NAMES = {
    "MOL_BOX_ORTHORHOMBIC": "mol_box_style",
    "MOL_BOX_TRICLINIC": "mol_box_style",
    "MOL_BOX_INFINITE": "mol_box_style"
}


class EnumsVisitor(c_ast.NodeVisitor):
    def __init__(self, *args, **kwargs):
        super(EnumsVisitor, self).__init__(*args, **kwargs)
        self.enums = []

    def visit(self, *args, **kwargs):
        super(EnumsVisitor, self).visit(*args, **kwargs)
        return self.enums

    def visit_Enum(self, node):
        first_value = node.values.enumerators[0].name
        name = ENUM_NAMES[first_value]
        enum = Enum(name)
        for enumerator in node.values.enumerators:
            enum.append(enumerator.name, enumerator.value)
        self.enums.append(enum)

class ArrayType(Ctype):
    '''Representing array type, with various dimensions'''

    def __init__(self, *args, **kwargs):
        super(ArrayType, self).__init__(*args, **kwargs)
        # Do we have a compile-time unknown dimension here ?
        self.unknown_dims = False
        self.all_dims = []
        self.is_ptr = True

    def set_dimensions(self, *all_dims):
        '''
        Set the array dimensions. For example, the C declaration
        `int (*bar)[3]` should be declared by calling in this function as
        `array_type.set_dimensions(-1, 3)`

        The -1 value indicate a dimension with unknown size at compile-time
        '''
        for dim_size in all_dims:
            self.all_dims.append(dim_size)
            if dim_size == -1:
                self.unknown_dims = True

class PtrToArrayType(ArrayType):
    '''
    A pointer to an array. This is used in chemfiles to provide view into
    memory owned by the C++ library.
    '''

    def __init__(self, *args, **kwargs):
        super(PtrToArrayType, self).__init__(*args, **kwargs)