message(VERBOSE "Configuring molcore/source...")
include(FetchContent)
# introduce deps


find_package(xtensor QUIET)
if(xtensor_FOUND)
    message(VERBOSE "local xtensor found")
else()
    message(VERBOSE "local xtensor not found, downloading from github...")
    FetchContent_Declare(
        xtl
        GIT_REPOSITORY https://github.com/xtensor-stack/xtl.git
        )
    FetchContent_Declare(
        xtensor 
        GIT_REPOSITORY https://github.com/xtensor-stack/xtensor.git
    )
    FetchContent_MakeAvailable(xtl xtensor)
endif()

find_package(xtensor-blas QUIET)
if(xtensor-blas_FOUND)
    message(VERBOSE "local xtensor-blas found")
else()
    message(VERBOSE "local xtensor-blas not found, downloading from github...")
    FetchContent_Declare(
        xtensor-blas
        GIT_REPOSITORY https://github.com/xtensor-stack/xtensor-blas.git
    )
    FetchContent_MakeAvailable(xtensor-blas)
endif()

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

# define target

file(GLOB_RECURSE MOLCORE_SRC "./*.cpp")
add_library(
    molcore_molcore
    ${MOLCORE_SRC}
)
    
target_include_directories(molcore_molcore PUBLIC ${xtensor_INCLUDE_DIRS})

target_link_libraries(molcore_molcore ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})