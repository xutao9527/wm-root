project(wm-net VERSION ${WM_VERSION})

# 查找Boost库
find_package(Boost REQUIRED COMPONENTS system)

# 添加可执行程序
add_executable(wm-net src/main.cpp)
target_include_directories(wm-net PRIVATE ${Boost_INCLUDE_DIRS})

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)