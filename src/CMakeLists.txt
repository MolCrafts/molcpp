set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(POSITION_INDEPENDENT_CODE ON)

set(SOURCE_CODE
    box.cpp
    # trajectory.cpp
    # frame.cpp
    # topology.cpp
    # connectivity.cpp

    # io/loader.cpp
)

if(BUILD_SHARED_LIBS MATCHES ON)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_CODE})
    target_compile_options(${PROJECT_NAME} PRIVATE
        -fPIC
        -Wall
        -Wextra
        -Wpedantic
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib
    )
elseif(BUILD_SHARED_LIBS MATCHES OFF)
    add_library(${PROJECT_NAME} STATIC ${SOURCE_CODE})
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/io
)