message("Configuring molcore/source...")
include(FetchContent)

file(GLOB_RECURSE MOLCORE_SRC "./*.cpp")
add_library(
    molcore_molcore
    ${MOLCORE_SRC}
)

add_definitions(-DHAVE_CBLAS=1)
if (WIN32)
    find_package(OpenBLAS REQUIRED)
    set(BLAS_LIBRARIES ${CMAKE_INSTALL_PREFIX}${OpenBLAS_LIBRARIES})
else()
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
endif()
message(STATUS "BLAS VENDOR:    " ${BLA_VENDOR})
message(STATUS "BLAS LIBRARIES: " ${BLAS_LIBRARIES})
target_link_libraries(molcore_molcore ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

find_package(xtl QUIET)
find_package(xtensor QUIET)
find_package(xtensor-blas QUIET)
