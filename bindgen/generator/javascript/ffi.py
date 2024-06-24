# -* coding: utf-8 -*

"""
This module generate the Typescript interface declaration for the functions it
finds in a C header. It only handle edge cases for the chemfiles.h header.
"""
from .constants import BEGINING
from .convert import return_type_to_js, arg_type_to_js
from generator import MOL_TYPES

MANUAL_DEFINITIONS = """
// === Manual declarations
declare const tag: unique symbol;
type POINTER = number & { readonly [tag]: 'pointer' };

export type CHFL_PTR = POINTER & { readonly [tag]: 'chemfiles pointer' };
type c_char_ptr = POINTER & { readonly [tag]: 'char pointer' };
type c_char_ptr_ptr = POINTER & { readonly [tag]: 'char array pointer' };
type c_bool_ptr = POINTER & { readonly [tag]: 'bool pointer' };
type c_double_ptr = POINTER & { readonly [tag]: 'double pointer' };
type c_uint64_ptr = POINTER & { readonly [tag]: 'uint64_t pointer' };
type chfl_bond_order_ptr = POINTER & { readonly [tag]: 'chfl_bond_order pointer' };
type chfl_property_kind_ptr = POINTER & { readonly [tag]: 'chfl_property_kind pointer' };
type chfl_cellshape_ptr = POINTER & { readonly [tag]: 'chfl_cellshape pointer' };
type function_ptr = POINTER & { readonly [tag]: 'function pointer' };

type c_char = number;
type c_bool = number;
type c_double = number;

type chfl_vector3d = c_double_ptr;
type chfl_match_ptr = POINTER;

type LLVMType = 'i8' | 'i16' | 'i32' | 'i64' | 'float' | 'double' | '*';

export interface EmscriptenModule {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    FS: any;

    HEAP8: Int8Array;
    HEAP16: Int16Array;
    HEAP32: Int32Array;
    HEAPU8: Uint8Array;
    HEAPU16: Uint16Array;
    HEAPU32: Uint32Array;
    HEAPF32: Float32Array;
    HEAPF64: Float64Array;

    getValue(ptr: POINTER, type: LLVMType): number;
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    setValue(ptr: POINTER, value: any, type: LLVMType): void;
    UTF8ToString(ptr: c_char_ptr, maxBytesToRead?: number): string;
    stringToUTF8(str: string, ptr: c_char_ptr, maxBytesToWrite: number): void;

    stackSave(): number;
    stackAlloc(size: number): POINTER;
    stackRestore(saved: number): void;

    // eslint-disable-next-line @typescript-eslint/ban-types
    addFunction(fn: Function, signature: string): function_ptr;

    _malloc(size: number): POINTER;
    _free(ptr: POINTER): void;
}

export declare function loadChemfiles(): Promise<ChemfilesModule>;
// === End of manual declarations

"""

PTR_TEMPLATE = "export type {name} = CHFL_PTR & {{ readonly [tag]: '{name}' }};\n"

FUNCTION_TEMPLATE = """    // '{name}' at {coord}
    _{name}({args}): {restype};
"""

EXTRA_EXPORTED_RUNTIME_METHODS = [
    "stringToUTF8",
    "UTF8ToString",
    "getValue",
    "setValue",
    "stackSave",
    "stackAlloc",
    "stackRestore",
    "addFunction",
    "FS",
]


def write_dts(filename, functions, enums):
    with open(filename, "w") as fd:
        fd.write(BEGINING)

        for name in EXTRA_EXPORTED_RUNTIME_METHODS:
            assert name in MANUAL_DEFINITIONS
        fd.write(MANUAL_DEFINITIONS)

        for name in MOL_TYPES:
            fd.write(PTR_TEMPLATE.format(name=name))

        for enum in enums:
            name = enum.name
            fd.write(f"export type {name} = number & {{ readonly [tag]: '{name}' }};\n")
            for enumerator in enum.enumerators:
                fd.write(f"export declare const {enumerator.name}: {name};\n")

        fd.write("\nexport interface ChemfilesModule extends EmscriptenModule {\n")
        for function in functions:
            fd.write(interface(function))
        fd.write("}\n\n")


def write_js(filename, enums):
    with open(filename, "w") as fd:
        fd.write(BEGINING)
        fd.write(
            """
/* eslint-disable */
const loadChemfiles = require('../../lib/libchemfiles');

module.exports = {
    loadChemfiles,
"""
        )

        for enum in enums:
            fd.write(f"    // {enum.name} values\n")
            for enumerator in enum.enumerators:
                fd.write(f"    {enumerator.name}: {enumerator.value.value},\n")

        fd.write("}\n")


def write_cmake_export(path, functions):
    with open(path, "w") as fd:
        fd.write('set(EXPORTED_FUNCTIONS\n"')
        fd.write(", ".join(["'_{}'".format(f.name) for f in functions]))
        fd.write('"\n)\n')

        fd.write('set(EXTRA_EXPORTED_RUNTIME_METHODS\n"')
        fd.write(
            ", ".join(["'{}'".format(name) for name in EXTRA_EXPORTED_RUNTIME_METHODS])
        )
        fd.write('"\n)\n')


def interface(function):
    names = []
    types = []
    for arg in function.args:
        if not arg.type.is_ptr and arg.type.cname == "uint64_t":
            # emscripten passes uint64_t as two uint32_t, for high and low bits
            # when working with chemfiles, we can (usually) ignore the high
            # bits, since uint64_t are used to store size_t values only, which
            # will be 32-bits on WASM (for now, while only wasm32 exists)
            names.append(arg.name + "_lo")
            names.append(arg.name + "_hi")
            types.append("number")
            types.append("number")
        else:
            names.append(arg.name)
            types.append(arg_type_to_js(arg.type))

    args = ", ".join(n + ": " + t for (n, t) in zip(names, types))

    restype = return_type_to_js(function.rettype)

    return FUNCTION_TEMPLATE.format(
        name=function.name,
        coord=function.coord,
        args=args,
        restype=restype,
    )