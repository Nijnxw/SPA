#pragma once

#include <string>
#include <stdexcept>

enum class RPNTokenType {
	VARIABLE,
	INTEGER,
	OPERATOR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS
};

class RPNToken {
private:
	RPNTokenType type;
	std::string contents;
	int precedence;

public:
	RPNToken(RPNTokenType type, std::string contents);

	std::string getContents() const;
	int getPrecedence() const;
	int comparePrecedence(RPNToken other);

	bool isVariable();
	bool isInteger();
	bool isOperator();
	bool isLeftParenthesis();
	bool isRightParenthesis();
};
