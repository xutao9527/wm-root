project(wm-net VERSION ${WM_VERSION})


find_package(Boost REQUIRED COMPONENTS system)

set(SRC_FILES  
    src/tcp_server.h
    src/tcp_server.cpp
)

add_library(wm-net ${SRC_FILES})
target_include_directories(wm-net PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}  
)
target_link_libraries(wm-net ${Boost_LIBRARIES})  # 链接Boost库

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)