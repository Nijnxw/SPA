#pragma once
#include <string>
#include <fstream>
#include <algorithm>

class CommonLexer {
public:
	CommonLexer(std::istream* new_stream);

protected:
    std::string nextStr;
    char peek();
    char next();
    bool notEOF();
    bool isValidInt(std::string str);
    bool isValidName(std::string str);

private:
    std::istream* stream;
};
