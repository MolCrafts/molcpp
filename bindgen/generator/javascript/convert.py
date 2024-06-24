# -* coding: utf-8 -*
"""
This module create the javascript version of C arguments, types, ...
"""
from generator.types import StringType, ArrayType, PtrToArrayType
from generator import MOL_TYPES

CONVERSIONS = {
    "double": "c_double",
    "bool": "c_bool",
    "char": "c_char",
    "uint64_t": 'c_uint64',

    "chfl_cellshape": "chfl_cellshape",
    "chfl_property_kind": "chfl_property_kind",
    "chfl_bond_order": "chfl_bond_order",
    "chfl_match": "chfl_match",

    "chfl_warning_callback": "number",
    "chfl_vector3d": "chfl_vector3d",
}


def return_type_to_js(typ):
    if isinstance(typ, StringType):
        return "c_char_ptr"
    else:
        assert typ.cname in ["chfl_status", "void", *MOL_TYPES]
        return typ.cname


def arg_type_to_js(typ):
    if isinstance(typ, ArrayType) and typ.cname == "char":
        return "c_char_ptr_ptr"
    elif typ.is_ptr:
        if typ.cname.startswith("CHFL_"):
            return typ.cname
        elif typ.cname == "void":
            return "CHFL_PTR"
        elif typ.cname == "chfl_vector3d":
            return "chfl_vector3d"
        else:
            return CONVERSIONS[typ.cname] + "_ptr"
    else:
        return CONVERSIONS[typ.cname]