cmake_minimum_required(VERSION 3.25)

#
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
add_definitions(-D_WIN32_WINNT=0x0A00)

# 设置wm版本
set(WM_VERSION "1.0.0" CACHE STRING "wm version")

# 设置项目名称
project(wm-root VERSION ${WM_VERSION})

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

# 设置编译选项
if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()

# 添加wm-net模块
# add_subdirectory(wm-net)

# 添加wm-core模块
add_subdirectory(wm-core)

# 添加wm-business模块
add_subdirectory(wm-app)

# 添加测试模块
# add_subdirectory(wm-tests)

