cmake_minimum_required(VERSION 3.22)

include(cmake/prelude.cmake)

project(
    molcpp
    VERSION 0.1.0
    DESCRIPTION "cross-platform molecular dynamics data structure and algorithm"
    HOMEPAGE_URL "https://github.com/Roy-Kid/molcpp.git"
    LANGUAGES CXX
)

# ---- Declare library ----
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(BUILD_SHARED_LIBS)
  add_library(molcpp SHARED)
else()
  add_library(molcpp STATIC)
endif()
add_subdirectory(src)

include(GenerateExportHeader)
generate_export_header(
    molcpp
    BASE_NAME molcpp
    EXPORT_FILE_NAME export/molcpp/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

set_target_properties(
    molcpp PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME molcpp
    OUTPUT_NAME molcpp
)

target_include_directories(
    molcpp ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    molcpp SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(molcpp PUBLIC cxx_std_20)

if (MOLCPP_DEV)
    enable_testing()
    add_subdirectory(tests)
endif()