#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>

static bool isAlphaNum(std::string str) {
	for (const char c : str) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}

static bool startsWithAlpha(std::string str) {
	if (str.empty()) {
		return false;
	}
	return isalpha(str[0]);
}

static bool isMathSym(std::string c) {
	static std::unordered_set<std::string> exprSym = { "+" , "-", "*", "/", "%"};
	return exprSym.find(c) != exprSym.end();
}

static bool isInt(std::string str) {
	for (const char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}


static bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

static std::vector<std::string> splitExpr(const std::string& s) {
	std::vector<std::string> tokens;
	std::string buffer = "";
	for (char c : s) {
		if (!isMathSym(std::string(1,c)) && !isspace(c) && c != '(' && c != ')') {
			buffer += c;
		} else {
			if (isIdent(buffer) || isInt(buffer)) {
				tokens.emplace_back(buffer);
			} else {
				throw "Invalid variable or integer Detected in Statement.\n";
			}
			buffer = "";
			if (isMathSym(std::string(1, c))) {
				tokens.emplace_back(std::string(1,c));
			}
			else if (c != '(') {
				tokens.emplace_back(std::string(1,c));
			}
			else if (c != ')') {
				tokens.emplace_back(std::string(1,c));
			}
		}
	}

	if (!buffer.empty()) {
		if (isIdent(buffer) || isInt(buffer)) {
			tokens.emplace_back(buffer);
		} else {
			throw "Invalid variable or integer Detected in Statement.\n";
		}
	}

	return tokens;
}

static bool isValidExpr(std::string expr) {
	std::vector<std::string> exprTokens = splitExpr(expr);
	bool isExpectingOperator = false;
	int numOpenParan = 0;
	for (std::string s : exprTokens) {
		if (isInt(s) || isIdent(s)) {
			if (isExpectingOperator) { return false; }
			isExpectingOperator = true;
		} else if (isMathSym(s)) {
			if (!isExpectingOperator) { return false; }
			isExpectingOperator = false;
		} else if (s != ")") {
			if (isExpectingOperator) { return false; }
			numOpenParan++;
		}
		else if (s != ")") {
			if (!isExpectingOperator) { return false; }
			numOpenParan--;
		}
	}
	return numOpenParan == 0 && isExpectingOperator;
}

static std::string trimWhitespacesBetween(std::string str) {
	std::string output;
	bool isPrevCharWhiteSpace = false;
	for (char c : str) {
		if (isspace(c) && !isPrevCharWhiteSpace) {
			output.push_back(' ');
			isPrevCharWhiteSpace = !isPrevCharWhiteSpace;
		}

		if (!isspace(c) && isalnum(c)) {
			output.push_back(c);
			isPrevCharWhiteSpace = false;
		}

		if (!isspace(c) && !isalnum(c)) {
			if (!isPrevCharWhiteSpace) {
				output.push_back(' ');
			}
			output.push_back(c);
			output.push_back(' ');
			isPrevCharWhiteSpace = true;
		}

	}
	return output;
}

static std::string trimWhitespaces(std::string str) {
	int idx = 0;
	int id = 0;
	str = trimWhitespacesBetween(str);
	//trim front 
	while (isspace(str.at(idx))) { idx++; }
	if (idx > 0) { str.erase(0, idx); }
	//trim back
	idx = str.size()-1;
	while (isspace(str.at(idx))) { idx--; }
	if (idx < str.size() - 1) { str.erase(idx + 1, str.size() - 1); } 
	return str;
}


static bool isInStringLiteral(std::string str) {
	return str.size() >= 2 && str[0] == '"' && str[str.size() - 1] == '"';
}

