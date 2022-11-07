#include <syntax_analyzer.h>
#include <tokenizer.h>
#include <error.h>

#include <gtest/gtest.h>

#include <string>
#include <utility>

TEST(syntax_analyzer_tests, valid_expression_tests) {
    std::string s = "(x & y) -> z";
    std::vector<Token> tokens = Read(std::move(s));
    ASSERT_TRUE(IsValidExpression(tokens));

    s = "(x -> y) <-> (z & !w)";
    tokens = Read(std::move(s));


}

TEST(syntax_analyzer_tests, invalid_constant_token_tests) {
    std::vector<Token> tokens = Read("x | 2");
    try {
        IsValidExpression(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_STREQ("invalid number 2!", e.what());
    } catch(...) {
        FAIL() << "Expected syntax error";
    }

    tokens = Read("(x -> y) & 123");
    try {
        IsValidExpression(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_STREQ("invalid number 123!", e.what());
    } catch(...) {
        FAIL() << "Expected syntax error";
    }
}

TEST(syntax_analyzer_tests, invalid_symbol_tests) {
    std::vector<Token> tokens = Read("(x -> y) & A");

    try {
        IsValidExpression(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_STREQ("invalid symbol A!", e.what());
    } catch(...) {
        FAIL() << "Expected syntax error";
    }

    tokens = Read("x | test");
    try {
        IsValidExpression(tokens);
    } catch (const SyntaxError& e) {
        EXPECT_STREQ("invalid symbol test!", e.what());
    } catch(...) {
        FAIL() << "Expected syntax error";
    }
}

TEST(syntax_analyzer_tests, invalid_bracket_sequence_tests) {
    std::vector<Token> tokens = Read("");
}




