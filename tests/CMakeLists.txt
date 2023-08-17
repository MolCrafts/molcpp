set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

set(TEST_EXE ${PROJECT_NAME}_test)

add_executable(${TEST_EXE}
    main.cpp
    test_vec3.cpp
    test_mat3.cpp
    test_geom.cpp
    test_dict.cpp
)

find_package(doctest QUIET)
if (NOT doctest_FOUND)
include(FetchContent)
FetchContent_Declare(
  DocTest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.11
)
FetchContent_MakeAvailable(DocTest)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${TEST_EXE})
endif()

target_link_libraries(${TEST_EXE} PRIVATE doctest::doctest molcpp)

