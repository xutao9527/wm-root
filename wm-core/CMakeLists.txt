project(wm-core VERSION ${WM_VERSION})

find_package(Boost REQUIRED COMPONENTS system)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

# 自动扫描 src 目录下的所有 .cpp 和 .hpp 文件
file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "src/*.hpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
    src/pre/pch.hpp
)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
