set(TOKENIZER_TESTS tokenizer_test.cpp)
enable_testing()

#if (BUILD_TESTING)
    add_executable(logical_expression_tokenizer_tests ${TOKENIZER_TESTS})


    target_link_libraries(
            logical_expression_tokenizer_tests
            gtest_main
            logical_expression_tokenizer
    )


    include(GoogleTest)
    gtest_discover_tests(logical_expression_tokenizer_tests)
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    #add_test(logical_expression_tokenizer_tests logical_expression_tokenizer_tests)
#    target_include_directories(
#            logical_expression_tokenizer_tests
#            PUBLIC
#            logical_expression_tokenizer
#    )
    #gtest_discover_tests(logical_expression_tokenizer_tests)
#    add_test(logical_expression_tokenizer_tests logical_expression_tokenizer_tests)
    #gtest_discover_tests(logical_expression_tokenizer_tests)
#    logical_expression_tokenizer_tests logical_expression_tokenizer_tests)
#endif()

#target_link_libraries(logical_expression_tokenizer_tests logical_expression_tokenizer)