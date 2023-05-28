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

if(BUILD_SHARED_LIBS)
  set(POSITION_INDEPENDENT_CODE ON)
endif()

add_library(molcpp)

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
else()
  message(STATUS "Chemfiles not installed, compile from source code")
  message(STATUS "git submodule update...")
  execute_process(
    COMMAND git submodule update --init --recursive external/chemfiles
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_subdirectory(${CMAKE_MODULE_PATH}/chemfiles)
endif()

find_package(xtensor QUIET)

if(xtensor_FOUND)
  message(STATUS "xtensor installed")
  target_include_directories(
    molcpp
    PUBLIC
    ${xtensor_INCLUDE_DIRS}
  )
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
  execute_process(
    COMMAND git submodule update --init --recursive external/xtensor-blas
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_definitions(-DHAVE_CBLAS=1)

  if(WIN32)
    find_package(OpenBLAS REQUIRED)
    set(BLAS_LIBRARIES ${CMAKE_INSTALL_PREFIX}${OpenBLAS_LIBRARIES})
  else()
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
  endif()

  message(STATUS "BLAS VENDOR:    " ${BLA_VENDOR})
  message(STATUS "BLAS LIBRARIES: " ${BLAS_LIBRARIES})

  add_subdirectory(${CMAKE_MODULE_PATH}/xtl)
  add_subdirectory(${CMAKE_MODULE_PATH}/xtensor)
  add_subdirectory(${CMAKE_MODULE_PATH}/xtensor-blas)
endif()

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

  # src/forcefield.cpp
  src/atom.cpp
  src/bond.cpp
  src/topology.cpp

  # src/element.cpp
  # src/frame.cpp
  # src/trajectory.cpp
  # src/cell.cpp
)

target_link_libraries(
  molcpp
  PUBLIC
  chemfiles
  xtl
  xtensor
  xtensor-blas
  ${BLAS_LIBRARIES}
  ${LAPACK_LIBRARIES}
)

# For debug and test
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Compile molcpp and its testcases in debug mode")
  enable_testing() # enable_testing must at top cmakelists
  add_subdirectory(tests)

# For release
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "Release build.")
else()
  message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()
