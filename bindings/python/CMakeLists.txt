cmake_minimum_required(VERSION 3.24)

project(molcpp LANGUAGES CXX)
set(Python_FIND_VIRTUALENV ONLY)
find_package(Python 3.10 COMPONENTS Interpreter Development.Module REQUIRED NumPy)

include(CMakePrintHelpers)
cmake_print_variables(Python_ROOT_DIR)
cmake_print_variables(Python_EXECUTABLE)

find_package(pybind11 REQUIRED CONFIG)
find_package(xtensor REQUIRED)
find_package(xtensor-python REQUIRED)
pybind11_add_module(molcpp 
    space.cpp
)
find_package(molcpp REQUIRED CONFIG)

target_link_libraries(molcpp PUBLIC pybind11::module xtensor-python)
target_link_libraries(molcpp PRIVATE Python::NumPy)
target_link_libraries(molcpp PUBLIC molcpp::molcpp)

target_compile_definitions(molcpp PRIVATE VERSION_INFO=0.1.0)
install(TARGETS molcpp LIBRARY DESTINATION .)