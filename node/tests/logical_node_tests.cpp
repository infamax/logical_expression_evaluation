#include <gtest/gtest.h>

#include <node.h>
#include <memory>

TEST(logical_node_tests, simple_expression_test) {
    // expression x ^ 1 = !x
    int x = 0;
    auto var = std::make_shared<VariableNode>(x);
    auto digit = std::make_shared<DigitNode>(1);
    auto expr = std::make_shared<LogicalOperationNode>(Op::XOR, var, digit);
    x = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    ASSERT_EQ(expr->Evaluate(), 0);
}

TEST(logical_node_tests, expression_with_disjunction) {
    // expression x | y
    int x = 0;
    int y = 0;
    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto expr = std::make_shared<LogicalOperationNode>(Op::OR, var1, var2);

    x = 0;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 0;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(logical_node_tests, expression_with_conjunction) {
    // expression x & y
    int x = 0;
    int y = 0;
    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto expr = std::make_shared<LogicalOperationNode>(Op::AND, var1, var2);

    x = 0;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 0;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(logical_node_tests, expression_with_xor) {
    // expression x ^ y
    int x = 0;
    int y = 0;
    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto expr = std::make_shared<LogicalOperationNode>(Op::XOR, var1, var2);

    x = 0;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 0;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 0);
}

TEST(logical_node_tests, test_expression_with_implication) {
    int x = 0;
    int y = 0;
    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto expr = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, var1, var2);

    x = 0;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(logical_node_tests, test_expression_with_equivalence) {
    int x = 0;
    int y = 0;
    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto expr = std::make_shared<LogicalOperationNode>(Op::EQUIVALENCE, var1, var2);

    x = 0;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(logical_node_tests, hard_expression_test1) {
    // expression (x -> y) -> ((x -> z) -> (x -> y & z))
    int x = 0;
    int y = 0;
    int z = 0;

    auto var1 = std::make_shared<VariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(y);
    auto var3 = std::make_shared<VariableNode>(z);

    auto impl_expr1 = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, var1, var2);
    auto impl_expr2 = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, var1, var3);
    auto and_expr1 = std::make_shared<LogicalOperationNode>(Op::AND, var2, var3);
    auto impl_expr3 = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, var1, and_expr1);
    auto impl_expr4 = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, impl_expr2, impl_expr3);
    auto expr = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, impl_expr3, impl_expr4);

    x = 0;
    y = 0;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 0;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 1;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 1;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}

TEST(logical_node_tests, hard_expression_test2) {
    // expression [((!x <-> z) | (x ^ y)) & (x ^ !y)] -> z
    int x = 0;
    int y = 0;
    int z = 0;
    auto var1 = std::make_shared<NotVariableNode>(x);
    auto var2 = std::make_shared<VariableNode>(z);
    auto var3 = std::make_shared<VariableNode>(x);
    auto var4 = std::make_shared<VariableNode>(y);
    auto var5 = std::make_shared<NotVariableNode>(y);

    auto equivalence1 = std::make_shared<LogicalOperationNode>(Op::EQUIVALENCE, var1, var2);
    auto xor1 = std::make_shared<LogicalOperationNode>(Op::XOR, var3, var4);
    auto xor2 = std::make_shared<LogicalOperationNode>(Op::XOR, var3, var5);
    auto or1 = std::make_shared<LogicalOperationNode>(Op::OR, equivalence1, xor1);
    auto and1 = std::make_shared<LogicalOperationNode>(Op::AND, or1, xor2);
    auto expr = std::make_shared<LogicalOperationNode>(Op::IMPLICATION, and1, var2);

    x = 0;
    y = 0;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 0;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 0;
    y = 1;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 0;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);

    x = 1;
    y = 1;
    z = 0;
    ASSERT_EQ(expr->Evaluate(), 0);

    x = 1;
    y = 1;
    z = 1;
    ASSERT_EQ(expr->Evaluate(), 1);
}