cmake_minimum_required(VERSION 3.16)

project(molcpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "SHARED" ON)

# CMake helpers
include(CMakePrintHelpers)

# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
# cmake_print_variables(CMAKE_MODULE_PATH)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(MOLCPP_BUILD_SHARED)
  add_library(molcpp SHARED)
else()
  add_library(molcpp STATIC)
  set(POSITION_INDEPENDENT_CODE ON)
endif()

# Add dependencies
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

find_package(chemfiles QUIET)
if(chemfiles_FOUND)
  message(STATUS "Chemfiles installed")
  target_include_directories(
    molcpp
    PUBLIC
    ${chemfiles_INCLUDE_DIRS}      
  )
  target_include_directories(
    molcpp
    PUBLIC
    ${chemfiles_INCLUDE_DIRS}
  )
else()
  message(STATUS "Chemfiles not installed, compile from source code")
  message(STATUS "git submodule update...")
  execute_process(
    COMMAND git submodule update --init --recursive external/chemfiles
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_subdirectory(${CMAKE_MODULE_PATH}/chemfiles)
endif()

target_include_directories(
  molcpp
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(
  molcpp
  PRIVATE
  # independent
  src/algo.cpp
  src/linalg.cpp
  src/element.cpp
  src/itemtype.cpp
  # dependent
  src/forcefield.cpp
  src/atom.cpp
  src/bond.cpp
  src/topology.cpp
  src/frame.cpp
  src/trajectory.cpp
  src/cell.cpp
  # src/celllist.cpp
  # src/neighborlist.cpp
)

target_link_libraries(
  molcpp
  PUBLIC
  chemfiles
)

# For debug and test
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Compile molcpp and its testcases in debug mode")
  target_compile_options(molcpp
    PUBLIC
    -O0
    -Wall
    -g
  )
  enable_testing() # enable_testing must at top cmakelists
  add_subdirectory(tests)

# For release
# For release
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "Release build.")
else()
  message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()
