if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(logical_expression_syntax_analyzer syntax_analyzer.cpp)


target_include_directories(
        logical_expression_syntax_analyzer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        logical_expression_syntax_analyzer
        logical_expression_tokenizer
)