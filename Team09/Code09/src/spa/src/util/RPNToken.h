#pragma once

#include <string>
#include <stdexcept>

enum class TokenType {
	Variable,
	Integer,
	Operator,
	LeftParenthesis,
	RightParenthesis
};

class RPNToken {
private:
	TokenType type;
	std::string contents;
	int precedence;

public:
	RPNToken(TokenType type, std::string contents);

	std::string getContents() const;
	int getPrecedence() const;
	int comparePrecedence(RPNToken other);

	bool isVariable();
	bool isInteger();
	bool isOperator();
	bool isLeftParenthesis();
	bool isRightParenthesis();
};