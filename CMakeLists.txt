cmake_minimum_required(VERSION 3.15)

set(WM_VERSION "1.0.0" CACHE STRING "wm version")
project(wm-root VERSION ${WM_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()


add_subdirectory(wm-net)
# add_subdirectory(wm-protocol)
# add_subdirectory(wm-business)

