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