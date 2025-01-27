add_library(wm-business)

target_include_directories(wm-business
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 添加源文件
file(GLOB_RECURSE WM_BUSINESS_SOURCES src/*.cpp)
target_sources(wm-business PRIVATE ${WM_BUSINESS_SOURCES})

# 设置测试
enable_testing()
add_subdirectory(tests) 