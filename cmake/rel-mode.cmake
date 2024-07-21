message("release config")

include(cmake/folders.cmake)

option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" OFF)
if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(test)
endif()

option(BUILD_DOCS "Build documentation using Doxygen" OFF)
# if(BUILD_MCSS_DOCS)
#   include(cmake/docs.cmake)
# endif()

# --- build bindings ---
if(molcpp_BUILD_PYTHON)
  add_subdirectory(bindings/python)
endif()


add_folders(Project)
