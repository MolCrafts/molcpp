find_package(Python REQUIRED COMPONENTS Interpreter Development.Module NumPy)
find_package(pybind11 REQUIRED CONFIG)
find_package(xtensor REQUIRED)
find_package(xtensor-python REQUIRED)

pybind11_add_module(molcpp-python 
    space.cpp
)
include(CMakePrintHelpers)
cmake_print_variables(${Python_EXECUTABLE})
target_include_directories(molcpp-python PRIVATE "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")
set_target_properties(
    molcpp-python PROPERTIES
    OUTPUT_NAME molcpp
)

target_link_libraries(molcpp-python PUBLIC pybind11::module xtensor-python Python::NumPy)
target_link_libraries(molcpp-python PRIVATE molcpp::molcpp)

target_compile_definitions(molcpp-python PRIVATE VERSION_INFO=0.1.0)
