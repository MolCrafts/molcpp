message("release config")

include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

option(BUILD_DOCS "Build documentation using Doxygen" OFF)
# if(BUILD_MCSS_DOCS)
#   include(cmake/docs.cmake)
# endif()

option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" OFF)


add_folders(Project)
