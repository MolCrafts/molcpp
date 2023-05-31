message(STATUS "Building tests")
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# get test data
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests-data")
  # 如果不存在则下载
  message(STATUS "Downloading test data...")
  execute_process(
    COMMAND git clone https://github.com/chemfiles/tests-data.git
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  )
else()
  # 如果存在则跳过下载
  message(STATUS "Test data already downloaded, skipping...")
endif()

# enable_testing()
add_executable(
  molcpp_test
  test_algo.cpp
  test_dict.cpp
  # test_itemtype.cpp
  # test_forcefield.cpp
  test_atom.cpp
  test_bond.cpp
  test_topology.cpp
  # test_frame.cpp
  # test_trajectory.cpp
  # test_cell.cpp
  # test_element.cpp
)

target_link_libraries(
  molcpp_test
  GTest::gtest_main
  molcpp
)

include(GoogleTest)
gtest_discover_tests(molcpp_test)