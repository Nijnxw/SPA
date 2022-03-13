#include "simple_parser/Token.h"

Token::Token(TokenType t, std::string v) : CommonToken(t, std::move(v)){}
NameToken::NameToken(std::string v) : Token(TokenType::NAME, std::move(v)){}
IntegerToken::IntegerToken(std::string v) : Token(TokenType::INTEGER, std::move(v)){}
TerminalToken::TerminalToken(std::string v) : Token(SPStringTokenMap[v], std::move(v)){}
EndOfFileToken::EndOfFileToken() : Token(TokenType::END_OF_FILE, ""){}