#include "Commons/CommonLexer.h"

CommonLexer::CommonLexer(std::istream* new_stream) : stream(new_stream) {}

char CommonLexer::next() { return stream->get(); }

char CommonLexer::peek() { return stream->peek(); }

bool CommonLexer::notEOF() { return !stream->eof(); }