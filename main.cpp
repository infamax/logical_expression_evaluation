#include <sstream>
#include <iostream>
#include <variant>

#include <tokenizer.h>

int main() {

    std::istringstream s("x | y");
//
    Tokenizer tokenizer(&s);
    if (tokenizer.IsEnd()) {
        std::cout << "Is Bad\n";
        return 0;
    }
//
    //tokenizer.Next();
//
    if (tokenizer.GetToken() == Token{SymbolToken{"x"}}) {
        std::cout << "good1!\n";
        //return 0;
    } else {
        std::cout << "bad!\n";
    }

    tokenizer.Next();
//

//
//    tokenizer.Next();
//
    if (tokenizer.GetToken() == Token{LogicalToken{"|"}}) {
        std::cout << "good2!\n";
    }

//
//    if (tokenizer.IsEnd()) {
//        std::cout << "bad\n";
//        return 0;
//    }
//
//    tokenizer.Next();
//
//    if (tokenizer.GetToken() == Token{SymbolToken{"y"}}) {
//        std::cout << "good\n";
//    }
//
//    std::cout << std::get<SymbolToken>(tokenizer.GetToken()).name << std::endl;
//
//    if (tokenizer.IsEnd()) {
//        std::cout << "good end\n";
//    }

    return 0;
}
