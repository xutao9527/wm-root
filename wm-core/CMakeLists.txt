project(wm-core VERSION ${WM_VERSION})

find_package(Boost REQUIRED COMPONENTS system)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")


add_library(${PROJECT_NAME} 
    src/conf/server_conf.hpp
    src/conf/server_conf.cpp
    src/net/server.hpp
    src/net/server.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)


target_precompile_headers(${PROJECT_NAME} PRIVATE
    src/common/pch.h
)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
