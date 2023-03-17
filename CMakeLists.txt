cmake_minimum_required(VERSION 3.16)

project(molcpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# CMake helpers
include(CMakePrintHelpers)
# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
# cmake_print_variables(CMAKE_MODULE_PATH)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/libs)

add_subdirectory(${CMAKE_MODULE_PATH}/chemfiles)
add_subdirectory(${CMAKE_MODULE_PATH}/xtl)
add_subdirectory(${CMAKE_MODULE_PATH}/xtensor)

add_library(molcpp)

target_include_directories(
  molcpp
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_sources(
  molcpp
  PRIVATE
  src/algo.cpp
  src/element.cpp
  src/graph.cpp
  src/atom.cpp
  src/bond.cpp
  src/molecule.cpp
  # src/trajectory.cpp
  src/topology.cpp
  # src/frame.cpp
  src/parsmart.cpp
)

target_link_libraries(
  molcpp
  PUBLIC
  chemfiles
  xtl
  xtensor
)

# For debug and test
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_options(molcpp
      PUBLIC
          -Wall
          -g
  )
  enable_testing()
  add_subdirectory(tests)
  
endif()
