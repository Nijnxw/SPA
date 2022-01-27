#include "util/RPN.h"
#include "util/RPNToken.h"

//constructor
RPN::RPN(std::string equation) {
	eqn = equation;
	rpn = convertToRpn(eqn);
}

//getters
std::vector<std::string> RPN::getRpnNotation() const {
	std::vector<std::string> output;
	for (int i = 0; i < rpn.size(); i++) {
		output.push_back(rpn.at(i).getContents());
	}
	return output;
}

std::string RPN::getInfixNotation() const {
	return eqn;
}

//check if this rpn contains the other rpn
bool RPN::contains(RPN other) {
	std::vector<std::string> thisRpn = this->getRpnNotation();
	std::vector<std::string> otherRpn = other.getRpnNotation();
	if (thisRpn.size() < otherRpn.size()) throw std::runtime_error("RPN elements length mismatch.\n");
	for (int i = 0; i < thisRpn.size() - otherRpn.size() + 1; i++) {
		bool match = true;
		for (int j = 0; j < otherRpn.size(); j++) {
			if (thisRpn[i + j] != otherRpn[j]) match = false;
		}
		if (match) return match;
	}
	return false;
}

// HELPER IDENTIFIER FUNCTIONS
bool isOperator(std::string token) {
	return (token == "+" || token == "-" || token == "*" || token == "/" || token == "%");
}

bool isNumber(std::string token) {
	for (int i = 0; i < token.length(); i++) {
		if (!isdigit(token[i])) return false;
	}
	return true;
}

bool isWhitespace(std::string token) {
	for (int i = 0; i < token.length(); i++) {
		if (!isspace(token[i])) return false;
	}
	return true;
}

bool isVariable(std::string token) {
	if (token.length() == 0) return false;
	if (!isalpha(token[0])) return false;
	for (int i = 1; i < token.length(); i++) {
		if (!isalpha(token[i]) && !isdigit(token[i])) return false;
	}
	return true;
}

bool isLeftParenthesis(std::string token) {
	return token == "(";
}

bool isRightParenthesis(std::string token) {
	return token == ")";
}

std::vector<RPNToken> tokenize(std::string exp) {
	std::vector<RPNToken> tokens;
	std::string buffer;

	for (int i = 0; i < exp.length(); i++) {
		std::string character(1, exp[i]);

		//number or letter: add to number buffer
		if (!isOperator(character) && !isWhitespace(character) &&
			!isLeftParenthesis(character) && !isRightParenthesis(character)) {
			buffer.append(character);
		//other characters detected - flush buffer before adding the new character
		} else {
			if (buffer.size() > 0) {
				if (isVariable(buffer)) {
					tokens.push_back(RPNToken(TokenType::Variable, buffer));
				} else if (isNumber(buffer)) {
					tokens.push_back(RPNToken(TokenType::Integer, buffer));
				} else {
					throw std::runtime_error("Invalid Token Detected in Statement.\n");
				}
			}
			buffer = "";
			if (isOperator(character)) {
				tokens.push_back(RPNToken(TokenType::Operator, character));
			} else if (isLeftParenthesis(character)) {
				tokens.push_back(RPNToken(TokenType::LeftParenthesis, character));
			} else if (isRightParenthesis(character)) {
				tokens.push_back(RPNToken(TokenType::RightParenthesis, character));
			}
		}
	}

	//final flush
	if (buffer.size() > 0) {
		if (isVariable(buffer)) {
			tokens.push_back(RPNToken(TokenType::Variable, buffer));
		} else {
			tokens.push_back(RPNToken(TokenType::Integer, buffer));
		}
	}
	if (tokens.size() <= 0) throw std::runtime_error("No tokens Detected.\n");
	return tokens;
}

//takes in equation in infix notation and returns RPN notation
std::vector<RPNToken> RPN::convertToRpn(std::string infix) {
	std::vector<RPNToken> out;
	std::stack<RPNToken> stack;
	std::string output;
	std::vector<RPNToken> tokens = tokenize(infix);

	for (int i = 0; i < tokens.size(); i++) {
		RPNToken token = tokens[i];

		if (token.isInteger() || token.isVariable()) {
			out.push_back(token);
		} else if (token.isOperator()) {
			if (!stack.empty()) {
				RPNToken top = stack.top();
				while (!stack.empty() && top.comparePrecedence(token) >= 0) {
					stack.pop();
					out.push_back(top);

					if (!stack.empty()) {
						top = stack.top();
					}
				}
			}
			stack.push(token);
		} else if (token.isLeftParenthesis()) {
			stack.push(token);
		} else {
			bool matched = false;
			while (!stack.empty() && !matched) {
				out.push_back(stack.top());
				stack.pop();

				if (!stack.empty() && stack.top().isLeftParenthesis()) {
					matched = true;
					stack.pop();
				}
			}

			if (stack.empty() && !matched) throw std::runtime_error("Non Matching Parentheses Detected.\n");
		}
	}

	while (!stack.empty()) {
		if (stack.top().isLeftParenthesis()) throw std::runtime_error("Non Matching Parentheses Detected.\n");
		out.push_back(stack.top());
		stack.pop();
	}
	return out;
}
