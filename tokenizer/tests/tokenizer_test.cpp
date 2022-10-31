#include <tokenizer.h>

#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

TEST(tokenizer_test, simple_logical_expression_test) {
    std::stringstream ss("x | y");
    Tokenizer tokenizer(&ss);
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"x"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"|"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"y"}});

    tokenizer.Next();
    ASSERT_TRUE(tokenizer.IsEnd());
}

TEST(tokenizer_test, expression_with_brackets) {
    std::stringstream ss("(x | y) & z");
    Tokenizer tokenizer(&ss);
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::OPEN_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"x"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"|"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"y"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::CLOSE_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"&"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"z"}});

    tokenizer.Next();
    ASSERT_TRUE(tokenizer.IsEnd());
}

TEST(tokenizer_test, empty_expression) {
    std::stringstream ss(" ");
    Tokenizer tokenizer(&ss);
    ASSERT_TRUE(tokenizer.IsEnd());
}

TEST(tokenizer_test, tokenize_heavy_expression) {
    std::stringstream ss("!((]x ^ y) -> (!z <-> q)) & 2");
    Tokenizer tokenizer(&ss);
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"!"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::OPEN_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::OPEN_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::SQUARE_CLOSE_BRACKET});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"x"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"^"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"y"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::CLOSE_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"->"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::OPEN_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"!"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"z"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"<->"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{SymbolToken{"q"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::CLOSE_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{BracketToken::CLOSE_PAREN});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"&"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{ConstantToken{2}});

    tokenizer.Next();
    ASSERT_TRUE(tokenizer.IsEnd());
}

TEST(tokenizer_test, empty_expression_with_many_spaces) {
    std::stringstream ss("     ");
    Tokenizer tokenizer(&ss);
    ASSERT_TRUE(tokenizer.IsEnd());
}

TEST(tokenizer_test, constant_expression) {
    std::stringstream ss("1 | 0");
    Tokenizer tokenizer(&ss);
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{ConstantToken{1}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{LogicalToken{"|"}});

    tokenizer.Next();
    ASSERT_FALSE(tokenizer.IsEnd());
    ASSERT_EQ(tokenizer.GetToken(), Token{ConstantToken{0}});

    tokenizer.Next();
    ASSERT_TRUE(tokenizer.IsEnd());
}