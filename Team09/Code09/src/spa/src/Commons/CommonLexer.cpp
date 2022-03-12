#include "Commons/CommonLexer.h"

CommonLexer::CommonLexer(std::istream* new_stream) : stream(new_stream) {}

char CommonLexer::next() { return stream->get(); }

char CommonLexer::peek() { return stream->peek(); }

bool CommonLexer::notEOF() { return !stream->eof(); }

bool CommonLexer::isValidInt(std::string str) {
	if ( str.empty() || str[0] == '0') { return false; }
	for (const char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool CommonLexer::isValidName(std::string str) {
	if (str.empty() || !isalpha(str[0])) { return false; }
	for (const char c : str) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}