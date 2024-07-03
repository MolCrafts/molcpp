#!/usr/bin/env python3
# -* coding: utf-8 -*
import os
import sys
from generator.ffi import FFI
from generator import python


def usage():
    name = sys.argv[0]
    langs = "python"
    print("Usage: {} molcpp.h {} out/path".format(name, langs))


def parse_args(args):
    return {
        "header": args[1],
        "binding": args[2],
        "outpath": args[3],
    }


# def generate_fortran(config):
#     ffi = FFI(config["header"])
#     root = config["outpath"]

#     fortran.write_enums(os.path.join(root, "enums.f90"), ffi.enums)
#     fortran.write_definitions(root, ffi.functions)


def generate_python(config):
    ffi = FFI(config["header"])
    root = config["outpath"]
    python.write_ffi(os.path.join(root, "ffi.py"), ffi.enums, ffi.functions)


# def generate_julia(config):
#     ffi = FFI(config["header"])
#     root = config["outpath"]
#     julia.write_types(os.path.join(root, "types.jl"), ffi.enums)
#     julia.write_functions(os.path.join(root, "cdef.jl"), ffi.functions)


# def generate_rust(config):
#     ffi = FFI(config["header"])
#     root = config["outpath"]
#     rust.write_ffi(os.path.join(root, "lib.rs"), ffi)


# def generate_js(config):
#     ffi = FFI(config["header"])
#     root = config["outpath"]
#     javascript.write_cmake_export(os.path.join(root, "exported.cmake"), ffi.functions)
#     javascript.write_js(os.path.join(root, "index.js"), ffi.enums)
#     javascript.write_dts(os.path.join(root, "index.d.ts"), ffi.functions, ffi.enums)


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print(sys.argv)
        usage()
        sys.exit(1)
    config = parse_args(sys.argv)
    
    # if config["binding"] == "fortran":
    #     generate_fortran(config)
    if config["binding"] == "python":
        generate_python(config)
    # elif config["binding"] == "julia":
    #     generate_julia(config)
    # elif config["binding"] == "rust":
    #     generate_rust(config)
    # elif config["binding"] == "js":
    #     generate_js(config)
    else:
        usage()
        print("Unkown binding type: {}".format(config["binding"]))
        sys.exit(2)