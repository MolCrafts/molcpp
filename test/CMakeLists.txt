cmake_minimum_required(VERSION 3.14)

project(molcoreTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(molcore REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(molcore_test source/molcore_test.cpp)
target_link_libraries(molcore_test PRIVATE molcore::molcore)
target_compile_features(molcore_test PRIVATE cxx_std_20)

add_test(NAME molcore_test COMMAND molcore_test)

# ---- End-of-file commands ----

add_folders(Test)
