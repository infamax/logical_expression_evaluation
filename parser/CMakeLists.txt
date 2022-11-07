if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(logical_expression_parser parser.cpp)

target_include_directories(
        logical_node
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        logical_expression_parser
        logical_expression_tokenizer
        logical_expression_syntax_analyzer
        logical_node
)

