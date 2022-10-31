#include "tokenizer.h"

#include <unordered_map>
#include <iostream>

bool ConstantToken::operator==(const ConstantToken& other) const {
    return value == other.value;
}

bool SymbolToken::operator==(const SymbolToken& other) const {
    return name == other.name;
}

bool LogicalToken::operator==(const LogicalToken& other) const {
    return name == other.name;
}

bool EmptyToken::operator==(const EmptyToken &other) const {
    return true;
}

Tokenizer::Tokenizer(std::istream *in): in_(in), token(ReadToken()) {}

bool Tokenizer::IsEnd() {
    if (token == Token{EmptyToken{}}) {
        return true;
    }
    return is_end_;
}

void Tokenizer::Next() {
    if (in_->eof() || token == Token{EmptyToken{}}) {
        is_end_ = true;
        return;
    }

   token = ReadToken();
}

Token Tokenizer::GetToken() {
    return token;
}

std::vector<Token> Read(const std::string& s) {
    std::stringstream ss(s);
    Tokenizer tokenizer(&ss);
    std::vector<Token> res;
    while (!tokenizer.IsEnd()) {
        res.push_back(tokenizer.GetToken());
        tokenizer.Next();
    }
    return res;
}

Token Tokenizer::ReadToken() {
    std::string s;
    std::unordered_map<std::string, bool> classes_token = {
            {"SymbolToken", false},
            {"LogicalToken", false},
            {"ConstantToken", false},
            {"BracketToken", false}
    };
    char c;

    while (!in_->eof()) {
        c = in_->peek();
        if (classes_token["ConstantToken"] && !(c >= '1' && c <= '9')) {
            return ConstantToken{std::stoi(s)};
        }

        if ((classes_token["SymbolToken"] | classes_token["LogicalToken"])
            && ((c >= '1' && c <= '9') || (c == '(' || c == ')' || c == '['
                 || c == ']' || c == '{' || c == '}') || c == ' ')) {
            if (s == "->" || s == "<->") {
                return LogicalToken{s};
            }
            return SymbolToken{s};
        }

        if (c == '(') {
            c = in_->get();
            return BracketToken::OPEN_PAREN;
        } else if (c == ')') {
            c = in_->get();
            return BracketToken::CLOSE_PAREN;
        } else if (c == '[') {
            c = in_->get();
            return BracketToken::SQUARE_OPEN_BRACKET;
        } else if (c == ']') {
            c = in_->get();
            return BracketToken::SQUARE_CLOSE_BRACKET;
        } else if (c == '{') {
            c = in_->get();
            return BracketToken::CURLY_OPEN_BRACKET;
        } else if (c == '}') {
            c = in_->get();
            return BracketToken::CURLY_CLOSE_BRACKET;
        }

        if (c == '&' || c == '^' ||
            c == '!' || c == '|') {
            c = in_->get();
            s += c;
            return LogicalToken{s};
        }

        if (c >= '0' && c <= '9' ) {
            classes_token["ConstantToken"] = true;
        } else if (c != ' ') {
            classes_token["SymbolToken"] = true;
            classes_token["LogicalToken"] = true;
        }

        if (c != ' ' && c != EOF) {
            s += c;
        }

        c = in_->get();
    }

    if (s == "(") {
        c = in_->get();
        return BracketToken::OPEN_PAREN;
    } else if (s == ")") {
        c = in_->get();
        return BracketToken::CLOSE_PAREN;
    } else if (s == "[") {
        c = in_->get();
        return BracketToken::SQUARE_OPEN_BRACKET;
    } else if (s == "]") {
        c = in_->get();
        return BracketToken::SQUARE_CLOSE_BRACKET;
    } else if (s == "{") {
        c = in_->get();
        return BracketToken::CURLY_OPEN_BRACKET;
    } else if (s == "}") {
        c = in_->get();
        return BracketToken::CURLY_CLOSE_BRACKET;
    }

    if (classes_token["ConstantToken"]) {
        return ConstantToken{std::stoi(s)};
    }


    if ((classes_token["SymbolToken"] | classes_token["LogicalToken"])) {
        if (s == "->" || s == "<->") {
            return LogicalToken{s};
        }
    }

    if (!s.empty()) {
        return SymbolToken{s};
    }

    return EmptyToken{};
}