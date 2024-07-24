cmake_minimum_required(VERSION 3.18..3.20)

project(molcpp-python)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module NumPy)
find_package(pybind11 REQUIRED CONFIG)
find_package(xtensor REQUIRED)
find_package(xtensor-python REQUIRED)

pybind11_add_module(molcpp main.cpp)
target_link_libraries(molcpp PUBLIC pybind11::module xtensor-python Python::NumPy)

target_compile_definitions(molcpp PRIVATE VERSION_INFO=0.1.0)