#include "simple_parser/Lexer.h"
#include "simple_parser/Token.h"

#include <cctype>
#include <string>
#include <vector>

Lexer::Lexer(std::istream* new_stream) : stream(new_stream){}

char Lexer::peek() {
    return stream->peek();
}

char Lexer::next() {
    return stream->get();
}

void Lexer::readName() {
    while (isalnum(peek()) != 0) {
        nextStr += next();
    }
}

void Lexer::readInteger() {
    while(isdigit(peek()) != 0) {
        nextStr += next();
    }
}

std::vector<Token*> Lexer::tokenize() {
    char nextChar;

    while (!stream->eof()) {
        nextChar = next();
        if (nextChar == EOF) {
            break;
        }

        nextStr += nextChar;
        if (isspace(nextChar) != 0) {
            nextStr = "";
            continue;
        } else if (isalpha(nextChar) != 0) {
            readName();
            lexical_tokens.push_back(new NameToken(nextStr));
        } else if (isdigit((nextChar)) != 0) {
            readInteger();
            lexical_tokens.push_back(new IntegerToken(nextStr));
        }
        // symbols that appear on its own
        else if (nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' ||
                 nextChar == '%' || nextChar == ';' || nextChar == '(' || nextChar == ')' ||
                 nextChar == '{' || nextChar == '}') {
            lexical_tokens.push_back(new SymbolToken(nextStr));
        }
        // symbols that may combine with other symbols
        else if (nextChar == '=' || nextChar == '!' || nextChar == '>' || nextChar == '<') {
             if (peek() == '=') {
                 nextStr += next();
             }
             lexical_tokens.push_back(new SymbolToken(nextStr));
        }
        // validate || and && symbols
        else if (nextChar == '|' || nextChar == '&') {
            if (peek() == nextChar) {
                nextStr += next();
                lexical_tokens.push_back(new SymbolToken(nextStr));
            } else { // invalid SIMPLE syntax
                throw std::runtime_error("Invalid Syntax: Expected '" + std::to_string(nextChar) + "' but got '" + peek() + "' instead\n.");
            }
        } else { // invalid SIMPLE syntax
            throw std::runtime_error("Invalid SIMPLE Syntax.\n");
        }

        nextStr = "";
    }

    lexical_tokens.push_back(new EndOfFileToken());
    return lexical_tokens;
}