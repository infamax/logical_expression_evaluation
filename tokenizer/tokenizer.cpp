#include "tokenizer.h"

bool ConstantToken::operator==(const ConstantToken& other) const {
    return value == other.value;
}

bool SymbolToken::operator==(const SymbolToken& other) const {
    return name == other.name;
}

bool LogicalToken::operator==(const LogicalToken& other) const {
    return name == other.name;
}

Tokenizer::Tokenizer(std::istream *in): in_(in) {}

bool Tokenizer::IsEnd() {
    char c = in_->peek();
    while (!in_->eof() && c == ' ') {
        in_->get();
        c = in_->peek();
    }

    if (in_->eof()) {
        return true;
    }

    return false;
}

void Tokenizer::Next() {
    token = in_->get();
}

Token Tokenizer::GetToken() {
    if (token == '(') {
        return BracketToken::OPEN_PAREN;
    }

    if (token == ')') {
        return BracketToken::CLOSE_PAREN;
    }

    if (token == '[') {
        return BracketToken::SQUARE_OPEN_BRACKET;
    }

    if (token == ']') {
        return BracketToken::SQUARE_CLOSE_BRACKET;
    }

    if (token == '{') {
        return BracketToken::CURLY_OPEN_BRACKET;
    }

    if (token == '}') {
        return BracketToken::CURLY_CLOSE_BRACKET;
    }

    if (isdigit(token)) {
        return ConstantToken{int(token) - '0'};
    }

    if (token == '|' || token == '&' || token == '!'
    || token == '^') {
        return LogicalToken{std::string(1, token)};
    }

    if (token == '-') {
        char next_symbol = in_->peek();
        if (next_symbol == '>') {
            in_->get();
            return LogicalToken{"->"};
        } else {
            return SymbolToken{std::string{1, token}};
        }
    }

    if (token == '<') {
        char next_symbol = in_->peek();
        if (next_symbol == '-') {
            in_->get();
            char next_two_symbol = in_->peek();
            if (next_two_symbol == '>') {
                return LogicalToken{"<->"};
            } else {
                return SymbolToken{std::string(1, token) + std::string(1, next_symbol)};
            }
        } else {
            return SymbolToken{std::string(1, token)};
        }
    }

    return SymbolToken{std::string(1, token)};
}

