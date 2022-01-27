#include "RPNToken.h"

RPNToken::RPNToken(TokenType t, std::string c) {
	type = t;
	contents = c;
	
	if (t != TokenType::Operator) {
		precedence = -1;
	} else if (c == "*" || c == "/" || c == "%") {
		precedence = 3;
	} else if (c == "+" || c == "-") {
		precedence = 2;
	} else {
		throw std::runtime_error("Invalid Token Content.\n");
	}
}

std::string RPNToken::getContents() const {
	return contents;
}
int RPNToken::getPrecedence() const {
	return precedence;
}

// compares this token with other token and returns true if this token has higher precedence
int RPNToken::comparePrecedence(RPNToken other) {
	return this->getPrecedence() - other.getPrecedence();
}

bool RPNToken::isVariable() {
	return type == TokenType::Variable;
}

bool RPNToken::isInteger() {
	return type == TokenType::Integer;
}

bool RPNToken::isOperator() {
	return type == TokenType::Operator;
}

bool RPNToken::isLeftParenthesis() {
	return type == TokenType::LeftParenthesis;
}

bool RPNToken::isRightParenthesis() {
	return type == TokenType::RightParenthesis;
}
