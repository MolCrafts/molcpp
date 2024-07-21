cmake_minimum_required(VERSION 3.15...3.29)

project(molcpp_python LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(molcpp_python 
    space.cpp
)

