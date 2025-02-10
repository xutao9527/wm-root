project(wm-app VERSION ${WM_VERSION})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} wm-core)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}/resources"
        VERBATIM
)
add_dependencies(${PROJECT_NAME} copy_resources)
