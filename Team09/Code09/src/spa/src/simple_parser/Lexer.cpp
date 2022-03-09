#include "simple_parser/Lexer.h"

Lexer::Lexer(std::istream* new_stream) : CommonLexer(new_stream){}

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
    while (notEOF()) {
        nextChar = next();
        if (nextChar == EOF) {
            break;
        }

		nextStr += nextChar;
		// Ignore whitespaces
		if (isspace(nextChar) != 0) {
			nextStr = "";
			continue;
		}
		// NAME
		else if (isalpha(nextChar) != 0) {
			readName();
			lexical_tokens.push_back(new NameToken(nextStr));
		}
		// INTEGER
		else if (isdigit((nextChar)) != 0) {
			readInteger();
			lexical_tokens.push_back(new IntegerToken(nextStr));
		}
		// PUNCTUATOR : '{' | '}' | '(' | ')' | ';'
		else if (nextChar == '{' || nextChar == '}' || nextChar == '(' || nextChar == ')' || nextChar == ';') {
			lexical_tokens.push_back(new PunctuatorToken(nextStr));
		}
		// OPERATOR that appears on its own
		else if (nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == '%') {
			lexical_tokens.push_back(new OperatorToken(nextStr));
		}
		// OPERATOR that may combine with other OPERATOR
		else if (nextChar == '=' || nextChar == '!' || nextChar == '>' || nextChar == '<') {
			if (peek() == '=') {
				nextStr += next();
			}
			lexical_tokens.push_back(new OperatorToken(nextStr));
		}
		// validate '||' and '&&' operators
		else if (nextChar == '|' || nextChar == '&') {
			if (peek() == nextChar) {
				nextStr += next();
				lexical_tokens.push_back(new OperatorToken(nextStr));
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