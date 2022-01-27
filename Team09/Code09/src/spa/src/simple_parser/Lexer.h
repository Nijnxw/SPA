#pragma once

#include "simple_parser/Token.h"

#include <string>
#include <fstream>
#include <vector>

class Lexer {
    private:
        std::string nextStr;
        std::istream* stream;

        char peek();
        char next();
        void readName();
        void readInteger();

    public:
        std::vector<Token*> lexical_tokens;

        explicit Lexer(std::istream* new_stream);

        std::vector<Token*> tokenize();
};

