cmake_minimum_required(VERSION 3.14)

project(molcoreTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----
if(PROJECT_IS_TOP_LEVEL)
  find_package(molcore REQUIRED)
  enable_testing()
elseif()

endif()

find_package(Catch2 3 REQUIRED)
# ---- Tests ----

# TODO: auto find tests starts with "test_"
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "source/*.cpp")
message(STATUS "find test sources: ${TEST_SOURCES}")

add_executable(molcore_test ${TEST_SOURCES})
target_link_libraries(molcore_test PRIVATE molcore::molcore)
target_link_libraries(molcore_test PRIVATE Catch2::Catch2WithMain)
target_compile_features(molcore_test PRIVATE cxx_std_20)

include(Catch)
catch_discover_tests(molcore_test)

# add_test(NAME molcore_test COMMAND molcore_test)

# ---- End-of-file commands ----

add_folders(Test)
