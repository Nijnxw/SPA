#pragma once

#include "simple_parser/SPToken.h"
#include "Commons/CommonLexer.h"

#include <cctype>
#include <string>
#include <fstream>
#include <vector>

class SPLexer: CommonLexer {
    private:
        void readName();
        void readInteger();

    public:
        std::vector<SPToken*> tokens;
        explicit SPLexer(std::istream* new_stream);
        std::vector<SPToken*> tokenize();
};

