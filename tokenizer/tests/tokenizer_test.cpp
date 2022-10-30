#include "../tokenizer.h"

#include <sstream>

#include <gtest/gtest.h>

TEST(tokenizer_test, parsing_simple_logical_expression_test) {
    std::stringstream ss{"x | y"};
    Tokenizer tokenizer{&ss};
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
