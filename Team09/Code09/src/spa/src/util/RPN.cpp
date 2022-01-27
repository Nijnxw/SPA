#include "RPN.h"

//constructor
RPN::RPN(std::string equation) {
	eqn = equation;
	rpn = convertToRpn(eqn);
}

//getters
std::string RPN::getRpnNotation() const {
	std::string output = "";
	if (rpn.size() > 0) {
		for (int i = 0; i < rpn.size() - 1; i++) {
			output.append(rpn[i] + ",");
		}
		output.append(rpn[rpn.size() - 1]);
	}
	return output;
}

std::string RPN::getInfixNotation() const {
	return eqn;
}

//check if this rpn contains the other rpn
bool RPN::contains(RPN other) {
	//TO DO
	return true;
}

bool isOperator(std::string token) {
	return (token == "+" || token == "-" || token == "*" || token == "/");
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

std::vector<std::string> tokenize(std::string exp) {
	std::vector<std::string> tokens;
	std::string numBuffer;

	for (int i = 0; i < exp.length(); i++) {
		std::string token(1, exp[i]);

		//TODO: account for more types of whitespace
		
		//operator: flush number buffer then add both to output
		if (isOperator(token)) {
			if (numBuffer.size() > 0) {
				tokens.push_back(numBuffer);
			}
			numBuffer = "";
			tokens.push_back(token);
		//number: add to number buffer
		} else if (isNumber(token)) {
			numBuffer.append(token);
		//whitespace: flush number buffer
		} else if (isWhitespace(token)) {
			if (numBuffer.size() > 0) {
				tokens.push_back(numBuffer);
				numBuffer = "";
			}
		} else {
			throw std::runtime_error("Invalid Token Detected in Statement.\n");
		}
	}
	if (numBuffer.length() > 0) tokens.push_back(numBuffer);
	return tokens;
}

//takes in equation in infix notation and returns RPN notation
std::vector<std::string> RPN::convertToRpn(std::string infix) {
	std::vector<std::string> out;
	std::stack<std::string> stack;
	std::string output;
	std::vector<std::string> tokens = tokenize(infix);
	for (int i = 0; i < tokens.size(); i++) {
		std::string token = tokens[i];

		if (isNumber(token)) {
			out.push_back(token);
		} else {
			// stack not empty - pop elements
			if (!stack.empty()) {
				// order of operations: (*, /, %) > (+, -)
				//implementing +,- first
				std::string top = stack.top();
				while (!stack.empty() && isOperator(top)) {
					stack.pop();
					out.push_back(top);

					if (!stack.empty()) {
						top = stack.top();
					}
				}
			}
			stack.push(token);
		} 
	}

	while (!stack.empty()) {
		out.push_back(stack.top());
		stack.pop();
	}
	return out;
}
