cmake_minimum_required(VERSION 3.25)

# 设置vcpkg工具链
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

# 设置项目名称
set(WM_VERSION "1.0.0" CACHE STRING "wm version")
project(wm-root VERSION ${WM_VERSION})

# 设置编译选项
if(MSVC)
    add_compile_options(/bigobj)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()

# 设置Windows版本
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(wm-core)
add_subdirectory(wm-app)

