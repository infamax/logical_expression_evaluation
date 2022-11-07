#include <parser.h>

#include <stack>
#include <iostream>

const std::unordered_map<std::string, Op> logical_ops = {
        {"&", Op::AND},
        {"|", Op::OR},
        {"->", Op::IMPLICATION},
        {"<->", Op::EQUIVALENCE},
        {"^", Op::XOR}
};

const std::unordered_map<std::string, int> ops_precedence = {
        {"&", 5},
        {"|", 4},
        {"^", 3},
        {"->", 2},
        {"<->", 1}
};

std::shared_ptr<Node> Parse(std::vector<Token>& tokens, const std::unordered_map<std::string, int>& vars) {
    if (tokens.empty()) {
        return std::make_shared<DigitNode>(0);
    }

    std::stack<std::shared_ptr<Node>> values;
    std::stack<std::string> ops;

    auto token = tokens.begin();

    while (token != tokens.end()) {
        if (type_tokens.at(token->index()) == "ConstantToken") {
            values.push(std::make_shared<DigitNode>(std::get<ConstantToken>(*token).value));
        } else if (type_tokens.at(token->index()) == "SymbolToken") {
            values.push(std::make_shared<VariableNode>(vars.at(std::get<SymbolToken>(*token).value)));
        } else if (type_tokens.at(token->index()) == "LogicalToken") {
            // check is variable !x
            if (std::get<LogicalToken>(*token).value == "!" && token + 1 != tokens.end()) {
                auto next_token = token + 1;
                if (type_tokens.at(next_token->index()) == "SymbolToken") {
                    values.push(std::make_shared<NotVariableNode>(vars.at(std::get<SymbolToken>(*next_token).value)));
                    ++token;
                    ++token;
                    continue;
                }
            }

            auto op = std::get<LogicalToken>(*token).value;
            if (!ops.empty() && ops.top() != "("
                && ops_precedence.at(ops.top()) > ops_precedence.at(op)) {
                auto var1 = values.top();
                values.pop();
                auto var2 = values.top();
                values.pop();
                values.push(std::make_shared<LogicalOperationNode>(
                        logical_ops.at(ops.top()), var1, var2));
            }
            ops.push(op);
        } else if (type_tokens.at(token->index()) == "BracketToken") {
            if (std::get<BracketToken>(*token) == BracketToken::OPEN_PAREN) {
                ops.push("(");
                ++token;
                continue;
            }

            while(ops.top() != "(") {
                auto var1 = values.top();
                values.pop();
                auto var2 = values.top();
                values.pop();

                auto op = std::make_shared<LogicalOperationNode>(logical_ops.at(ops.top()), var2, var1);
                values.push(op);
                ops.pop();
            }
            ops.pop();
        }
        ++token;
    }

    while (!ops.empty()) {
        auto var1 = values.top();
        values.pop();
        auto var2 = values.top();
        values.pop();

        auto op = std::make_shared<LogicalOperationNode>(logical_ops.at(ops.top()), var2, var1);
        values.push(op);
        ops.pop();
    }

    return values.top();
}