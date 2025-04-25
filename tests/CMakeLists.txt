
find_package(doctest REQUIRED)
# ---- Tests ----
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
message(STATUS "find test sources: ${TEST_SOURCES}")

add_executable(molcpp_test ${TEST_SOURCES})
message(STATUS "add test executable: ${CMAKE_BINARY_DIR}/tests")
add_test(NAME molcpp_test COMMAND molcpp_test WORKING_DIRECTORY)
set_target_properties(molcpp_test PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(molcpp_test PRIVATE molcpp)
target_link_libraries(molcpp_test PRIVATE doctest::doctest)
target_compile_features(molcpp_test PRIVATE cxx_std_20)

include(doctest)
doctest_discover_tests(molcpp_test)
