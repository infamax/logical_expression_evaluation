#include "syntax_analyzer.h"
#include "error.h"

#include <variant>
#include <vector>
#include <string>
#include <unordered_set>

bool IsValidConstantToken(const ConstantToken& token);
bool IsValidSymbolToken(const SymbolToken& token);
bool IsSequenceBracketProper(const std::vector<BracketToken>& brackets);

bool IsValidExpression(const std::vector<Token>& tokens) {
    std::vector<BracketToken> bracket_tokens;

    for (const auto& token: tokens) {
        if (type_tokens.at(token.index()) == "ConstantToken") {
            if (!IsValidConstantToken(std::get<ConstantToken>(token))) {
                throw SyntaxError("invalid number " + std::to_string(std::get<ConstantToken>(token).value) + "!");
            }
        }

        if (type_tokens.at(token.index()) == "SymbolToken") {
            if (!IsValidSymbolToken(std::get<SymbolToken>(token))) {
                throw SyntaxError("invalid symbol " + (std::get<SymbolToken>(token)).value + "!");
            }
        }

        if (type_tokens.at(token.index()) == "BracketToken") {
            bracket_tokens.push_back(std::get<BracketToken>(token));
        }
    }

    if (!IsSequenceBracketProper(bracket_tokens)) {
        throw SyntaxError("invalid brackets!");
    }

    return true;
}

bool IsValidConstantToken(const ConstantToken& token) {
    return token == ConstantToken{0} | token == ConstantToken{1};
}

const std::unordered_set<std::string> GenerateSetValidSymbolTokens() {
    std::unordered_set<std::string> res;
    for (char c = 'a'; c <= 'z'; ++c) {
        res.insert(std::string(1, c));
    }
    return res;
}

const std::unordered_set<std::string> valid_symbol_tokens = GenerateSetValidSymbolTokens();

bool IsValidSymbolToken(const SymbolToken& token) {
    // valid can be symbols a, b, c, ... , x, y, z
    return valid_symbol_tokens.find(token.value) != end(valid_symbol_tokens);
}

bool IsSequenceBracketProper(const std::vector<BracketToken>& brackets) {
    size_t count_open_paren = 0;
    size_t count_close_paren = 0;
    size_t count_square_open_bracket = 0;
    size_t count_square_close_bracket = 0;
    size_t count_curly_open_bracket = 0;
    size_t count_curly_close_bracket = 0;

    for (const auto& bracket : brackets) {
        if (bracket == BracketToken::OPEN_PAREN) {
            ++count_open_paren;
        }

        if (bracket == BracketToken::CLOSE_PAREN) {
            ++count_close_paren;
        }

        if (bracket == BracketToken::SQUARE_OPEN_BRACKET) {
            ++count_square_open_bracket;
        }

        if (bracket == BracketToken::SQUARE_CLOSE_BRACKET) {
            ++count_square_close_bracket;
        }

        if (bracket == BracketToken::CURLY_OPEN_BRACKET) {
            ++count_curly_open_bracket;
        }

        if (bracket == BracketToken::CURLY_CLOSE_BRACKET) {
            ++count_curly_close_bracket;
        }

        if (count_close_paren > count_open_paren
            || count_curly_close_bracket > count_curly_open_bracket
            || count_square_close_bracket > count_square_open_bracket) {
            return false;
        }
    }

    if (count_close_paren > count_open_paren
        || count_curly_close_bracket > count_curly_open_bracket
        || count_square_close_bracket > count_square_open_bracket) {
        return false;
    }

    return true;
}

