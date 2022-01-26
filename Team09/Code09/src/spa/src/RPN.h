#include <string>
#include <vector>
#include <stack>

class RPN {

private:
	std::string eqn;
	std::string rpn;
	std::string convertToRpn(std::string);

public:
	RPN(std::string);
	std::string getRpnNotation() const;
	std::string getInfixNotation() const;
	bool contains(RPN other);
};