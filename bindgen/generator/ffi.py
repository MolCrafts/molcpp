# -* coding: utf-8 -*
import os
from pycparser import parse_file

from .functions import FunctionVisitor
from .ctype import EnumsVisitor

PRIVATE_INCLUDE = os.path.join(os.path.dirname(__file__), "include")


class FFI:
    """Representing a full Foreign Function Interface in Python"""

    def __init__(self, header):
        """Create a new FFI from a set of headers"""
        self.enums = []
        self.functions = []

        args = ["-E", "-I" + PRIVATE_INCLUDE, "-I" + os.path.dirname(header)]
        ast = parse_file(header, use_cpp=True, cpp_path="gcc", cpp_args=args)
        self.enums.extend(EnumsVisitor().visit(ast))
        self.functions.extend(FunctionVisitor().visit(ast))