message(VERBOSE "Configuring molcore/source...")
include(FetchContent)

# define target
file(GLOB_RECURSE MOLCORE_SRC "./*.cpp")
add_library(
    molcore_molcore
    ${MOLCORE_SRC}
)

# introduce deps
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)

add_definitions(-DHAVE_CBLAS=1)
if (WIN32)
    find_package(OpenBLAS REQUIRED)
    set(BLAS_LIBRARIES ${CMAKE_INSTALL_PREFIX}${OpenBLAS_LIBRARIES})
else()
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
endif()
message(VERBOSE "BLAS VENDOR:    " ${BLA_VENDOR})
message(VERBOSE "BLAS LIBRARIES: " ${BLAS_LIBRARIES})

target_link_libraries(molcore_molcore ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})