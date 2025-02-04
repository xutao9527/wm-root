project(wm-net VERSION ${WM_VERSION})

find_package(Boost REQUIRED COMPONENTS system)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

file(GLOB SRC_FILES "src/*.cpp" "src/*.h" "src/utils.hpp")

add_library(wm-net ${SRC_FILES} "src/singleton.h")
target_include_directories(wm-net PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
)
target_link_libraries(wm-net
        ${Boost_LIBRARIES}
        spdlog::spdlog
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)