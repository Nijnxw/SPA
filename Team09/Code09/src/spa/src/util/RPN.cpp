#include "util/RPN.h"
#include "util/RPNToken.h"

//check if this rpn contains the other rpn
bool RPN::contains(std::string rpn1, std::string rpn2) {
	if (rpn1.length() < rpn2.length()) throw std::runtime_error("RPN elements length mismatch.\n");
	return rpn1.find(rpn2) != std::string::npos;
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
					tokens.push_back(RPNToken(RPNTokenType::VARIABLE, buffer));
				} else if (isNumber(buffer)) {
					tokens.push_back(RPNToken(RPNTokenType::INTEGER, buffer));
				} else {
					throw std::runtime_error("Invalid Token Detected in Statement.\n");
				}
			}
			buffer = "";
			if (isOperator(character)) {
				tokens.push_back(RPNToken(RPNTokenType::OPERATOR, character));
			} else if (isLeftParenthesis(character)) {
				tokens.push_back(RPNToken(RPNTokenType::LEFT_PARENTHESIS, character));
			} else if (isRightParenthesis(character)) {
				tokens.push_back(RPNToken(RPNTokenType::RIGHT_PARENTHESIS, character));
			}
		}
	}

	//final flush
	if (buffer.size() > 0) {
		if (isVariable(buffer)) {
			tokens.push_back(RPNToken(RPNTokenType::VARIABLE, buffer));
		} else {
			tokens.push_back(RPNToken(RPNTokenType::INTEGER, buffer));
		}
	}
	if (tokens.size() <= 0) throw std::runtime_error("No tokens Detected.\n");
	return tokens;
}

//takes in equation in infix notation and returns RPN notation
std::string RPN::convertToRpn(std::string infix) {
	std::vector<std::string> rpn;
	std::stack<RPNToken> stack;
	std::vector<RPNToken> tokens = tokenize(infix);

	for (int i = 0; i < tokens.size(); i++) {
		RPNToken token = tokens[i];

		if (token.isInteger() || token.isVariable()) {
			rpn.push_back(token.getContents());
		} else if (token.isOperator()) {
			if (!stack.empty()) {
				RPNToken top = stack.top();
				while (!stack.empty() && top.comparePrecedence(token) >= 0) {
					stack.pop();
					rpn.push_back(top.getContents());

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
				rpn.push_back(stack.top().getContents());
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
		rpn.push_back(stack.top().getContents());
		stack.pop();
	}

	// construct output
	std::string output;
	for (int i = 0; i < rpn.size() - 1; i++) {
		output.append(rpn[i] + " ");
	}
	output.append(rpn[rpn.size() - 1]);
	return output;
}