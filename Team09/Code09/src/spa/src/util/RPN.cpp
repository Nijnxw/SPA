#include "util/RPN.h"
#include "util/RPNToken.h"

//string splitter util
std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> output;
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		output.push_back(item);
	}
	return output;
}

//check if this rpn contains the other rpn
bool RPN::contains(const std::string& rpn1, const std::string& rpn2) {
	const std::vector<std::string>& tokens1 = split(rpn1, ' ');
	const std::vector<std::string>& tokens2 = split(rpn2, ' ');
	if (tokens1.size() < tokens2.size()) return false;

	bool output = false;
	for (int start = 0; start <= tokens1.size() - tokens2.size(); start++) {
		bool isSubVector = true;
		for (int offset = 0; offset < tokens2.size(); offset++) {
			isSubVector = isSubVector && tokens2[offset] == tokens1[start + offset];
		}
		output = output || isSubVector;
	}
	return output;
}

// HELPER IDENTIFIER FUNCTIONS
bool isOperator(const std::string& token) {
	return (token == "+" || token == "-" || token == "*" || token == "/" || token == "%");
}

bool isNumber(const std::string& token) {
	for (int i = 0; i < token.length(); i++) {
		if (!isdigit(token[i])) return false;
	}
	return true;
}

bool isWhitespace(const std::string& token) {
	for (int i = 0; i < token.length(); i++) {
		if (!isspace(token[i])) return false;
	}
	return true;
}

bool isVariable(const std::string& token) {
	if (token.length() == 0) return false;
	if (!isalpha(token[0])) return false;
	for (int i = 1; i < token.length(); i++) {
		if (!isalpha(token[i]) && !isdigit(token[i])) return false;
	}
	return true;
}

bool isLeftParenthesis(const std::string& token) {
	return token == "(";
}

bool isRightParenthesis(const std::string& token) {
	return token == ")";
}

std::vector<RPNToken> tokenize(const std::string& exp) {
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
			if (!buffer.empty()) {
				if (isVariable(buffer)) {
					tokens.emplace_back(RPNTokenType::VARIABLE, buffer);
				} else if (isNumber(buffer)) {
					tokens.emplace_back(RPNTokenType::INTEGER, buffer);
				} else {
					throw std::runtime_error("Invalid Token Detected in Statement.\n");
				}
			}
			buffer = "";
			if (isOperator(character)) {
				tokens.emplace_back(RPNTokenType::OPERATOR, character);
			} else if (isLeftParenthesis(character)) {
				tokens.emplace_back(RPNTokenType::LEFT_PARENTHESIS, character);
			} else if (isRightParenthesis(character)) {
				tokens.emplace_back(RPNTokenType::RIGHT_PARENTHESIS, character);
			}
		}
	}

	//final flush
	if (!buffer.empty()) {
		if (isVariable(buffer)) {
			tokens.emplace_back(RPNTokenType::VARIABLE, buffer);
		} else {
			tokens.emplace_back(RPNTokenType::INTEGER, buffer);
		}
	}
	if (tokens.empty()) throw std::runtime_error("No tokens Detected.\n");
	return tokens;
}

//takes in equation in infix notation and returns RPN notation
std::string RPN::convertToRpn(const std::string& infix) {
	std::vector<std::string> rpn;
	std::stack<RPNToken> stack;
	const std::vector<RPNToken>& tokens = tokenize(infix);

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
				if (!stack.empty() && stack.top().isLeftParenthesis()) {
					matched = true;
					stack.pop();
				} else {
					rpn.push_back(stack.top().getContents());
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
