#pragma once

#include <variant>
#include <vector>

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

struct EmptyToken {
    bool operator==(const EmptyToken& other) const;
};

using Token = std::variant<SymbolToken, LogicalToken, ConstantToken, BracketToken, EmptyToken>;

class Tokenizer {
public:
    Tokenizer(std::istream* in);

    bool IsEnd();

    void Next();

    Token GetToken();
private:
    Token ReadToken();
    std::istream* in_;
    Token token;
    bool is_end_ = false;
};

std::vector<Token> Read(const std::string& s);


