#include <node.h>

int DigitNode::Evaluate() const {
    return value_;
}

int VariableNode::Evaluate() const {
    return var_;
}

int NotVariableNode::Evaluate() const {
    return !var_;
}

int LogicalOperationNode::Evaluate() const {
    switch (op_) {
        case Op::AND:
            return lhs_->Evaluate() & rhs_->Evaluate();
        case Op::OR:
            return lhs_->Evaluate() | rhs_->Evaluate();
        case Op::XOR:
            return lhs_->Evaluate() ^ rhs_->Evaluate();
        case Op::IMPLICATION:
            return !lhs_->Evaluate() | rhs_->Evaluate();
        case Op::EQUIVALENCE:
            return lhs_->Evaluate() == rhs_->Evaluate();
    }
}

void LogicalOperationNode::SetLeft(std::shared_ptr <Node> node) { lhs_ = node; }

void LogicalOperationNode::SetRight(std::shared_ptr <Node> node) { rhs_ = node; }

int calc_priority_op(Op op) {
    switch (op) {
        case Op::AND:
            return 5;
        case Op::OR:
            return 4;
        case Op::XOR:
            return 3;
        case Op::IMPLICATION:
            return 2;
        case Op::EQUIVALENCE:
            return 1;
    }
}