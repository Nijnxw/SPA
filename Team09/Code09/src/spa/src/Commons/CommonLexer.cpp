#include "Commons/CommonLexer.h"

CommonLexer::CommonLexer(std::istream* new_stream) : stream(new_stream) {}

char CommonLexer::next() { return stream->get(); }

char CommonLexer::peek() { return stream->peek(); }

bool CommonLexer::notEOF() { return !stream->eof(); }

bool CommonLexer::isValidInt(std::string str) {
	if (str.length() == 1 && isdigit(str[0])) { return true; }
	if ( str.empty() || str[0] == '0') { return false; }
	return std::all_of(str.begin(), str.end(),
										 [](char c) { return isdigit(c); });
}

bool CommonLexer::isValidName(std::string str) {
	if (str.empty() || !isalpha(str[0])) { return false; }
	return std::all_of(str.begin(), str.end(),
										 [](char c) { return isalnum(c); });
}