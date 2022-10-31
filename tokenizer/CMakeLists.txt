

if (BUILD_TESTING)
#    add_executable(logical_expression_tokenizer_tests ${TOKENIZER_TESTS})
#
#    target_link_libraries(logical_expression_tokenizer_tests
#            PRIVATE
#            GTest::GTest
#            ${PROJECT_NAME})
#
#    include(GoogleTest)
#    #gtest_discover_tests(logical_expression_tokenizer_tests)
#
#    add_test(logical_expression_tokenizer_gtests logical_expression_tokenizer_tests)
    add_subdirectory(tests)
endif()

add_library(logical_expression_tokenizer tokenizer.cpp)

target_include_directories(
        logical_expression_tokenizer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

#target_link_libraries(logical_expression_tokenizer)


#if (BUILD_TESTING)
#    target_link_libraries(logical_expression_tokenizer logical_expression_tokenizer_tests)
#else()

#endif()
