set(CMAKE_TOOLCHAIN_FILE ${EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_CXX_COMPILER emcc)

add_executable(moljs 
    bind_vec3.cpp
    bind_box.cpp
)
set_target_properties(moljs PROPERTIES
    LINK_FLAGS "--bind -s -DMANGLE_SUPPORT=1 --embind-emit-tsd moljs.d.ts "
    OUTPUT_NAME "molcpp")
target_link_libraries(moljs PRIVATE molcpp)