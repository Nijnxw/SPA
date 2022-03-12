#pragma once
#include <string>
#include <fstream>

class CommonLexer {
public:
	CommonLexer(std::istream* new_stream);

protected:
    std::string nextStr;
    char peek();
    char next();
    bool notEOF();

private:
    std::istream* stream;
};
