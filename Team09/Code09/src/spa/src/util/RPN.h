#include "util/RPNToken.h"

#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cctype>

class RPN {

private:
	std::string eqn;
	std::vector<RPNToken> rpn;
	std::vector<RPNToken> convertToRpn(std::string);

public:
	RPN(std::string);
	std::vector<std::string> getRpnNotation() const;
	std::string getInfixNotation() const;
	bool contains(RPN other);
};