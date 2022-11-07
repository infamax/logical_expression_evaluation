#pragma once

#include <memory>
#include <utility>

enum class Op {
    AND,
    OR,
    EQUIVALENCE,
    IMPLICATION,
    XOR
};

class Node {
public:
    virtual int Evaluate() const = 0;
};

class DigitNode : public Node {
public:
    DigitNode(int value) : value_(value) {}
    int Evaluate() const override;
private:
    const int value_;
};

class VariableNode : public Node {
public:
    VariableNode(const int& var) : var_(var) {}
    int Evaluate() const override;
private:
    const int& var_;
};

class NotVariableNode : public Node {
public:
    NotVariableNode(const int& var) : var_(var) {}
    int Evaluate() const override;
private:
    const int& var_;
};

int calc_priority_op(Op op);

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(Op op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :
        op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)), precedence(calc_priority_op(op)) {}

    LogicalOperationNode(Op op) : op_(op), precedence(calc_priority_op(op)) {}

    int Evaluate() const override;
    void SetLeft(std::shared_ptr<Node> node);
    void SetRight(std::shared_ptr<Node> node);

    const int precedence;
private:
    std::shared_ptr<Node> lhs_;
    std::shared_ptr<Node> rhs_;
    Op op_;
};

