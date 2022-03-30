#include "simple_parser/SPLexer.h"

SPLexer::SPLexer(std::istream* new_stream) : CommonLexer(new_stream){}

std::vector<SPToken*> SPLexer::tokenize() {
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
			tokens.push_back((SPToken*) new NameToken(nextStr));
		}
		// INTEGER
		else if (isdigit((nextChar)) != 0) {
			readInteger();
			if (!isValidInt(nextStr)) {
				throw std::runtime_error("Invalid Syntax: Integer should not have leading zeroes, but got'" + nextStr + "' instead.\n");
			}
			tokens.push_back((SPToken*) new IntegerToken(nextStr));
		}
		// PUNCTUATOR : '{' | '}' | '(' | ')' | ';'
		// OPERATOR that appears on its own
		else if (nextChar == '{' || nextChar == '}' || nextChar == '(' || nextChar == ')' || nextChar == ';'
					|| nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == '%') {
			tokens.push_back((SPToken*) new TerminalToken(nextStr));
		}
		// OPERATOR that may combine with other OPERATOR
		else if (nextChar == '=' || nextChar == '!' || nextChar == '>' || nextChar == '<') {
			if (peek() == '=') {
				nextStr += next();
			}
			tokens.push_back((SPToken*) new TerminalToken(nextStr));
		}
		// validate '||' and '&&' operators
		else if (nextChar == '|' || nextChar == '&') {
			if (peek() == nextChar) {
				nextStr += next();
				tokens.push_back((SPToken*) new TerminalToken(nextStr));
			} else { // invalid SIMPLE syntax
				throw std::runtime_error("Invalid Syntax: Expected '" + std::to_string(nextChar) + "' but got '" + peek() + "' instead.\n");
			}
		} else { // invalid SIMPLE syntax
			throw std::runtime_error("Invalid SIMPLE Syntax.\n");
		}

		nextStr = "";
	}

	tokens.push_back((SPToken*) new EndOfFileToken());
	return tokens;
}