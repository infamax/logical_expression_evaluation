#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include <syntax_analyzer.h>
#include <tokenizer.h>
#include <parser.h>

std::pair<std::unordered_map<std::string, int>,
        std::unordered_map<int, std::string>> get_vars(const std::vector<Token>& tokens) {
    std::unordered_map<std::string, int> vars;
    std::unordered_map<int, std::string> vars_by_num;
    int num = 0;
    for (const auto& token : tokens) {
        if (type_tokens.at(token.index()) == "SymbolToken") {
            if (vars.find(std::get<SymbolToken>(token).value) == end(vars)) {
                vars[std::get<SymbolToken>(token).value] = 0;
                vars_by_num[num] = std::get<SymbolToken>(token).value;
                ++num;
            }
        }
    }
    return std::make_pair(vars, vars_by_num);
}

int pow_integer_num(int n, int degree) {
    int mult = n;
    for (int i = 1; i < degree; ++i) {
        n *= mult;
    }
    return n;
}

std::vector<std::vector<int>> AllPossibleArgsLogicFunc(int n) {
    int count = pow_integer_num(2, n);
    std::vector<std::vector<int>> res;
    res.reserve(count);
    for (int x = 0; x < count; ++x) {
        std::vector<int> v(n);
        std::fill(v.begin(), v.end(), 0);
        for (int j = 0; j < n; ++j) {
            if (x & (1 << j)) {
                v[j] = 1;
            }
        }
        res.push_back(v);
    }
    return res;
}

std::pair<std::vector<std::vector<int>>, std::vector<int>> EvaluateExpr(
        const std::vector<Token>& tokens, std::unordered_map<std::string, int>& vars,
        const std::unordered_map<int, std::string>& vars_by_num) {
    int n = vars.size();
    std::cout << "n = " << n << "\n";
    int count = pow_integer_num(2, n);
    std::vector<std::vector<int>> all_possible_vars = AllPossibleArgsLogicFunc(n);
    std::vector<int> values_func;
    values_func.reserve(count);
    auto expr = Parse(tokens, vars);

    for (const auto& var: all_possible_vars) {
        for (int i = 0; i < var.size(); ++i) {
            vars[vars_by_num.at(i)] = var[i];
        }
        values_func.push_back(expr->Evaluate());
    }

    return std::make_pair(all_possible_vars, values_func);
}

void WriteAns(std::ostream& out, const std::string& logic_expr, const std::vector<std::vector<int>>& values,
              const std::vector<int>& values_func) {
    out << "function = " << logic_expr << "\n";
    for (int i = 0; i < values.size(); ++i) {
        out << "(";
        for (int j = 0; j < values[i].size(); ++j) {
            out << values[i][j];
            if (j != values[i].size() - 1) {
                out << ", ";
            }
        }
        out << ") -> ";
        out << values_func[i];
        out << "\n";
    }
    out << "---------------------\n";
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "expected first argument file name" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output;
    if (argc == 3) {
        output.open(argv[2]);
    }

    std::string logic_expr;
    while (std::getline(input, logic_expr)) {
        logic_expr.pop_back();
        std::vector<Token> tokens = Read(logic_expr);
        std::pair<std::unordered_map<std::string, int>,
                std::unordered_map<int, std::string>> vars = get_vars(tokens);
        std::pair<std::vector<std::vector<int>>, std::vector<int>> res = EvaluateExpr(
                tokens, vars.first, vars.second);
        if (argc == 3) {
            WriteAns(output, logic_expr, res.first, res.second);
        } else {
            WriteAns(std::cout, logic_expr, res.first, res.second);
        }
    }

    return 0;
}
