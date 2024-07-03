# -* coding: utf-8 -*
"""
This module create the python version of C arguments, types, ...
"""
from ..ctype import ArrayType, StringType, PtrToArrayType
from .. import MOL_TYPES

CONVERSIONS = {
    "double": "c_double",
    "uint64_t": "c_uint64",
    "int64_t": "c_int64",
    "bool": "c_bool",
    "char": "c_char",
    "MOL_BOX": "MOL_BOX",
    "MOL_BOX_STYLE": "MOL_BOX_STYLE"
}

NUMPY_CONVERSIONS = {
    "double": "np.float64",
    "uint64_t": "np.uint64",
    "bool": "np.bool",
    "char": "c_char"
}


def type_to_python(typ, argument=False):
    if isinstance(typ, StringType):
        return "c_char_p"
    elif isinstance(typ, ArrayType):
        if typ.cname == "char":
            return "POINTER(c_char_p)"
        else:
            return array_to_python(typ)
    else:
        if typ.is_ptr:
            if typ.cname == "void":
                return "c_void_p"
            else:
                return "POINTER(" + CONVERSIONS[typ.cname] + ")"
        else:
            return CONVERSIONS[typ.cname]


def array_to_python(typ):
    if isinstance(typ, PtrToArrayType):
        ctype = CONVERSIONS[typ.cname]
        res = "POINTER(POINTER(" + ctype + "))"
    elif typ.unknown_dims:
        ctype = NUMPY_CONVERSIONS[typ.cname]
        res = "ndpointer(" + ctype + ', flags="C_CONTIGUOUS"'
        res += ", ndim=" + str(len(typ.all_dims))
        res += ")"
    else:
        ctype = CONVERSIONS[typ.cname]
        shape = ", ".join(typ.all_dims)
        res = "ARRAY(" + ctype + ", (" + shape + "))"

    return res