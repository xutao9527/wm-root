add_library(wm-protocol)

target_include_directories(wm-protocol
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 添加源文件
file(GLOB_RECURSE WM_PROTOCOL_SOURCES src/*.cpp)
target_sources(wm-protocol PRIVATE ${WM_PROTOCOL_SOURCES})

# 设置测试
enable_testing()
add_subdirectory(tests) 