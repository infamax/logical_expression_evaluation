#include <gtest/gtest.h>

#include <parser.h>
#include <tokenizer.h>
#include <node.h>

#include <vector>
#include <memory>
#include <iostream>

TEST(parser_tests, expression_with_or_test) {
    std::vector<Token> tokens = Read("x | y");
    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 0;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(parser_tests, expression_with_and_test) {
    std::vector<Token> tokens = Read("x & y");
    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 0;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(parser_tests, expression_with_xor_test) {
    std::vector<Token> tokens = Read("x ^ y");
    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 0;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 0);
}

TEST(parser_tests, expression_with_implication_test) {
    std::vector<Token> tokens = Read("x -> y");
    ASSERT_EQ(tokens.size(), 3);

    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 0;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(parser_tests, expression_with_equivalence_test) {
    std::vector<Token> tokens = Read("x <-> y");
    ASSERT_EQ(tokens.size(), 3);

    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 0;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(parser_tests, hard_expression_test) {
    // expression [((!x <-> z) | (x ^ y)) & (x ^ !y)] -> z

    std::vector<Token> tokens = Read("(((!x <-> z) | (x ^ y)) & (x ^ !y)) -> z");
    ASSERT_EQ(tokens.size(), 25);

    std::unordered_map<std::string, int> vars = {
            {"x", 0},
            {"y", 0},
            {"z", 0}
    };

    auto expr = Parse(tokens, vars);

    vars["x"] = 0;
    vars["y"] = 0;
    vars["z"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 0;
    vars["y"] = 0;
    vars["z"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 0;
    vars["y"] = 1;
    vars["z"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 0;
    vars["y"] = 1;
    vars["z"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 0;
    vars["z"] = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 0;
    vars["z"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    vars["x"] = 1;
    vars["y"] = 1;
    vars["z"] = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    vars["x"] = 1;
    vars["y"] = 1;
    vars["z"] = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}
