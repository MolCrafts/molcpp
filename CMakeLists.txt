cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    molcpp
    VERSION 0.1.0
    DESCRIPTION "cross-platform molecular dynamics data structure and algorithm"
    HOMEPAGE_URL "https://github.com/Roy-Kid/molcpp.git"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_subdirectory(source)
add_library(molcpp::molcpp ALIAS molcpp_molcpp)

include(GenerateExportHeader)
generate_export_header(
    molcpp_molcpp
    BASE_NAME molcpp
    EXPORT_FILE_NAME export/molcpp/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(molcpp_molcpp PUBLIC MOLCPP_STATIC_DEFINE)
endif()

set_target_properties(
    molcpp_molcpp PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME molcpp
    OUTPUT_NAME molcpp
)

target_include_directories(
    molcpp_molcpp ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    molcpp_molcpp SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(molcpp_molcpp PUBLIC cxx_std_20 c_std_99)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----
if(molcpp_DEVELOPER_MODE)
  if(NOT PROJECT_IS_TOP_LEVEL)
    message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of molcpp"
    )
  endif()
  include(cmake/dev-mode.cmake)
else()
  include(cmake/rel-mode.cmake)
endif()