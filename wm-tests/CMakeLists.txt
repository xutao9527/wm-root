add_executable(net_test net_test.cpp )
target_link_libraries(net_test wm-net)

add_executable(net_app net_app.cpp )
target_link_libraries(net_app wm-net)