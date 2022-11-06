set(NODE_TESTS logical_node_tests.cpp)
enable_testing()

add_executable(logical_node_tests ${NODE_TESTS})

target_link_libraries(
        logical_node_tests
        gtest_main
        logical_node
)

include(GoogleTest)
gtest_discover_tests(logical_node_tests)