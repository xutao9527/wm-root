project(wm-net VERSION ${WM_VERSION})


find_package(Boost REQUIRED COMPONENTS system)

# 使用 file(GLOB) 扫描 src 目录下的源文件和头文件
file(GLOB SRC_FILES "src/*.cpp" "src/*.hpp")

message(STATUS "SRC_FILES: ${SRC_FILES}")

add_library(wm-net ${SRC_FILES})
target_include_directories(wm-net PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}  
)
target_link_libraries(wm-net ${Boost_LIBRARIES})  # 链接Boost库

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)