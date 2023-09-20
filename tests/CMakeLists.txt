set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TEST_EXE ${PROJECT_NAME}_test)

add_executable(${TEST_EXE}
  main.cpp
  test_vec3.cpp
  test_mat3.cpp
  test_approx.cpp
  test_box.cpp
  test_topology.cpp
  test_frame.cpp
  test_trajectory.cpp
)

find_package(doctest QUIET)

if(NOT doctest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    DocTest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
  )
  FetchContent_MakeAvailable(DocTest)

  include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
  doctest_discover_tests(${TEST_EXE})
endif()

target_include_directories(${TEST_EXE} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${TEST_EXE} PRIVATE
  doctest::doctest
  molcpp
)

set_target_properties(${TEST_EXE} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()