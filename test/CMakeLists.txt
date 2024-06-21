cmake_minimum_required(VERSION 3.14)

project(molcoreTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----
if(PROJECT_IS_TOP_LEVEL)
  find_package(molcore REQUIRED)
  enable_testing()
endif()

find_package(doctest REQUIRED)
# ---- Tests ----
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "source/*.cpp")
message(STATUS "find test sources: ${TEST_SOURCES}")

add_executable(molcore_test ${TEST_SOURCES})
target_link_libraries(molcore_test PRIVATE molcore::molcore)
target_link_libraries(molcore_test PRIVATE doctest::doctest)
target_compile_features(molcore_test PRIVATE cxx_std_20)

include(doctest)
doctest_discover_tests(molcore_test)

# ---- End-of-file commands ----

add_folders(Test)
