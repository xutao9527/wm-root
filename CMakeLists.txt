cmake_minimum_required(VERSION 3.10)


# 设置Boost相关环境变量
set(BOOST_ROOT "C:/Boost" CACHE PATH "Boost root directory")
set(BOOST_LIBRARYDIR "C:/Boost/lib" CACHE PATH "Boost library directory")

# 设置wm版本
set(WM_VERSION "1.0.0" CACHE STRING "wm version")


# 设置项目名称
project(wm-root VERSION ${WM_VERSION})

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# 设置编译选项
if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()


# 添加子目录
add_subdirectory(wm-net)
# add_subdirectory(wm-protocol)
# add_subdirectory(wm-business)

# 添加测试开关
option(BUILD_TESTS "Build tests" ON)
# 根据测试开关决定是否添加测试目录
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(wm-tests)
endif()