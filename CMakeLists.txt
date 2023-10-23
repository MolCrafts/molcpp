cmake_minimum_required(VERSION 3.15)

project(molcpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

option(PYTHON_API "Build python API" OFF)
option(JS_API "Build javascript API" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_subdirectory(src)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(src)
    add_subdirectory(tests)
endif()

find_package(chemfiles)
if(NOT chemfiles_FOUND)
    message(STATUS "chemfiles not found, clone from github")
    include(FetchContent)
    FetchContent_Declare(
        chemfiles
        GIT_REPOSITORY https://github.com/chemfiles/chemfiles.git
        GIT_TAG 0.10.4
    )
    FetchContent_MakeAvailable(chemfiles)
else()
    message(STATUS "chemfiles found")
    endif()

target_link_libraries(molcpp chemfiles)

if(PYTHON_API)
    add_subdirectory(wrappers/python)
endif()
if(JS_API)
    add_subdirectory(wrappers/js)
endif()