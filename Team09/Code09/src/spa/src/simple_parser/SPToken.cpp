#include "simple_parser/SPToken.h"

SPToken::SPToken(TokenType t, std::string v) : CommonToken(t, v){}
NameToken::NameToken(std::string v) : SPToken(TokenType::NAME, v){}
IntegerToken::IntegerToken(std::string v) : SPToken(TokenType::INTEGER, v){}
TerminalToken::TerminalToken(std::string v) : SPToken(SPStringTokenMap[v], v){}
EndOfFileToken::EndOfFileToken() : SPToken(TokenType::END_OF_FILE, ""){}