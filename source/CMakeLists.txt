message(STATUS "Configuring molcore/source...")

# introduce deps

find_package(xtensor REQUIRED)

# define target

file(GLOB_RECURSE MOLCORE_SRC "./*.cpp")
add_library(
    molcore_molcore
    ${MOLCORE_SRC}
)

target_include_directories(molcore_molcore PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(molcore_molcore PUBLIC xtensor)