#include "simple_parser/SPToken.h"

SPToken::SPToken(TokenType t, std::string v) : CommonToken(t, std::move(v)){}
NameToken::NameToken(std::string v) : SPToken(TokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : SPToken(TokenType::INTEGER, std::move(v)){}
TerminalToken::TerminalToken(std::string v) : SPToken(SPStringTokenMap[v], std::move(v)){}
EndOfFileToken::EndOfFileToken() : SPToken(TokenType::END_OF_FILE, ""){}