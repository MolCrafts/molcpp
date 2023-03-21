cmake_minimum_required(VERSION 3.16)

project(molcpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# CMake helpers
include(CMakePrintHelpers)
# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
# cmake_print_variables(CMAKE_MODULE_PATH)

# Set default build type to Release
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

# Add dependencies
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

add_subdirectory(${CMAKE_MODULE_PATH}/chemfiles)
add_subdirectory(${CMAKE_MODULE_PATH}/xtl)
add_subdirectory(${CMAKE_MODULE_PATH}/xtensor)

add_library(molcpp SHARED)

target_include_directories(
  molcpp
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(
  molcpp
  PRIVATE
  # src/algo.cpp
  # src/element.cpp
  # src/graph.cpp
  # src/atom.cpp
  # src/bond.cpp
  # src/molecule.cpp
  src/forcefield.cpp
  # src/trajectory.cpp
  # src/topology.cpp
  # src/frame.cpp
  # src/parsmart.cpp
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
  )
  enable_testing()
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
