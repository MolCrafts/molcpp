message(STATUS "Configuring molcpp/source...")

# introduce deps

find_package(xtensor REQUIRED)

# define target

file(GLOB_RECURSE MOLCORE_SRC "./*.cpp")
add_library(
    molcpp_molcpp
    ${MOLCORE_SRC}
)

target_include_directories(molcpp_molcpp PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(molcpp_molcpp PUBLIC xtensor)