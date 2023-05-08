cmake_minimum_required(VERSION 3.16)

project(molcpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# CMake helpers
include(CMakePrintHelpers)
# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
# cmake_print_variables(CMAKE_MODULE_PATH)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add dependencies
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

find_package(chemfiles)
if(chemfiles_FOUND)
  message(STATUS "Chemfiles installed")
else()
  message(STATUS "Chemfiles not installed, compile from source code")
  execute_process(
    COMMAND git submodule update --init --recursive external/chemfiles
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
  add_subdirectory(${CMAKE_MODULE_PATH}/chemfiles)
endif()

find_package(xtensor)
if(xtensor_FOUND)
  message(STATUS "xtensor installed")
else()
  message(STATUS "xtensor not installed, compile from source code")
  execute_process(
    COMMAND git submodule update --init --recursive external/xtl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
  execute_process(
    COMMAND git submodule update --init --recursive external/xtensor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_subdirectory(${CMAKE_MODULE_PATH}/xtl)
  add_subdirectory(${CMAKE_MODULE_PATH}/xtensor)
endif()

add_library(molcpp SHARED)

target_include_directories(
  molcpp
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(
  molcpp
  PRIVATE
  src/algo.cpp
  src/itemtype.cpp
  src/atom.cpp
  src/bond.cpp
  src/forcefield.cpp
  # src/element.cpp
  # src/topology.cpp
  # src/frame.cpp
  # src/trajectory.cpp
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
  message(STATUS "Debug build.")
  target_compile_options(molcpp
      PUBLIC
          -Wall
          -g
          -ftest-coverage
  )
  add_subdirectory(tests)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "Release build.")
  target_compile_options(molcpp
      PUBLIC
          -O3
  )
  # install(TARGETS molcpp DESTINATION lib)
  # install(DIRECTORY include/ DESTINATION include)
else()
  message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()
