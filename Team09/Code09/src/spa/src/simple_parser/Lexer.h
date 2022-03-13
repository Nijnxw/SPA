#pragma once

#include "simple_parser/Token.h"
#include "Commons/CommonLexer.h"

#include <cctype>
#include <string>
#include <fstream>
#include <vector>

class Lexer:CommonLexer {
    private:
        void readName();
        void readInteger();

    public:
        std::vector<Token*> tokens;
        explicit Lexer(std::istream* new_stream);
        std::vector<Token*> tokenize();
};

