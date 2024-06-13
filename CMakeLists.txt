cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    molcore
    VERSION 0.1.0
    DESCRIPTION "cross-platform molecular dynamics data structure and algorithm"
    HOMEPAGE_URL "https://github.com/Roy-Kid/molcore.git"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    molcore_molcore
    source/molcore.cpp
)
add_library(molcore::molcore ALIAS molcore_molcore)

include(GenerateExportHeader)
generate_export_header(
    molcore_molcore
    BASE_NAME molcore
    EXPORT_FILE_NAME export/molcore/molcore_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(molcore_molcore PUBLIC MOLCORE_STATIC_DEFINE)
endif()

set_target_properties(
    molcore_molcore PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME molcore
    OUTPUT_NAME molcore
)

target_include_directories(
    molcore_molcore ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    molcore_molcore SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(molcore_molcore PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT molcore_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of molcore"
  )
endif()

include(cmake/dev-mode.cmake)
