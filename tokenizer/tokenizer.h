#pragma once

#include <variant>
#include <optional>
#include <istream>

struct SymbolToken {
    std::string name;

    bool operator==(const SymbolToken&) const;
};

struct LogicalToken {
    std::string name;

    bool operator==(const LogicalToken&) const;
};

struct ConstantToken {
    int value;

    bool operator==(const ConstantToken&) const;
};

enum class BracketToken {
    OPEN_PAREN,
    CLOSE_PAREN,
    SQUARE_OPEN_BRACKET,
    SQUARE_CLOSE_BRACKET,
    CURLY_OPEN_BRACKET,
    CURLY_CLOSE_BRACKET,
};

using Token = std::variant<SymbolToken, LogicalToken, ConstantToken, BracketToken>;

class Tokenizer {
public:
    Tokenizer(std::istream* in);

    bool IsEnd();

    void Next();

    Token GetToken();

private:
    std::istream* in_;
    char token;
};


