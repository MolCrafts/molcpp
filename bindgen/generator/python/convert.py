# -* coding: utf-8 -*
"""
This module create the python version of C arguments, types, ...
"""
from generator.types import ArrayType, StringType, PtrToArrayType
from generator import MOL_TYPES

CONVERSIONS = {
    "double": "c_double",
    "uint64_t": "c_uint64",
    "int64_t": "c_int64",
    "bool": "c_bool",
    "char": "c_char",
    "MOL_BOX": "MOL_BOX"
}

NUMPY_CONVERSIONS = {
    "double": "np.float64",
    "uint64_t": "np.uint64",
    "bool": "np.bool",
    "char": "c_char",
    "mol_vec3": "mol_vec3",
}


def type_to_python(typ, argument=False):
    if isinstance(typ, StringType):
        return "c_char_p"
    elif isinstance(typ, ArrayType):
        if typ.name == "char":
            return "POINTER(c_char_p)"
        else:
            return array_to_python(typ)
    else:
        if typ.is_ptr:
            if typ.name == "void":
                return "c_void_p"
            else:
                return "POINTER(" + CONVERSIONS[typ.name] + ")"
        else:
            return CONVERSIONS[typ.name]


def array_to_python(typ):
    if isinstance(typ, PtrToArrayType):
        ctype = CONVERSIONS[typ.name]
        res = "POINTER(POINTER(" + ctype + "))"
    elif typ.unknown_dims:
        ctype = NUMPY_CONVERSIONS[typ.name]
        res = "ndpointer(" + ctype + ', flags="C_CONTIGUOUS"'
        res += ", ndim=" + str(len(typ.all_dims))
        res += ")"
    else:
        ctype = CONVERSIONS[typ.name]
        shape = ", ".join(typ.all_dims)
        res = "ARRAY(" + ctype + ", (" + shape + "))"

    return res