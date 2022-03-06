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

static std::vector<std::string> splitExpr(const std::string& s, char delim) {
	std::vector<std::string> output;
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		output.push_back(item);
	}
	return output;
}

static bool isIdent(std::string str) {
	return startsWithAlpha(str) && isAlphaNum(str);
}

static bool isValidExpr(std::string expr) {
	std::vector<std::string> exprTokens = splitExpr(expr, ' ');
	bool isExpectingOperator = false;
	int numOpenParan = 0;
	for (std::string str : exprTokens) {
		if (isInt(str) || isIdent(str)) {
			if (isExpectingOperator) { return false;}
			isExpectingOperator = true;
		} else if (isMathSym(str)) {
			if (!isExpectingOperator) { return false; }
			isExpectingOperator = false;
		} else {
			if (str == "(") {
				numOpenParan++;
				isExpectingOperator = false;
			} else {
				if (!isExpectingOperator) { return false; }
				numOpenParan--;
				isExpectingOperator = true;
			}
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

