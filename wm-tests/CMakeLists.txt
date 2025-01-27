add_executable(net_test net_test.cpp)
target_link_libraries(net_test wm-net)

add_test(NAME net_test COMMAND net_test)
set_tests_properties(net_test PROPERTIES TIMEOUT 1)