cmake_minimum_required(VERSION 3.15)

project(wm-root VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wm-root wm-net/src/main.cpp)

# 添加子项目
# add_subdirectory(wm-net)
# add_subdirectory(wm-protocol)
# add_subdirectory(wm-business)

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/out)