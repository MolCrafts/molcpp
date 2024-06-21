cmake_minimum_required(VERSION 3.14)

project(molcppTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----
if(PROJECT_IS_TOP_LEVEL)
  find_package(molcpp REQUIRED)
  enable_testing()
endif()

find_package(doctest REQUIRED)
# ---- Tests ----
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "source/*.cpp")
message(STATUS "find test sources: ${TEST_SOURCES}")

add_executable(molcpp_test ${TEST_SOURCES})
target_link_libraries(molcpp_test PRIVATE molcpp::molcpp)
target_link_libraries(molcpp_test PRIVATE doctest::doctest)
target_compile_features(molcpp_test PRIVATE cxx_std_20)

include(doctest)
doctest_discover_tests(molcpp_test)

# ---- End-of-file commands ----

add_folders(Test)
