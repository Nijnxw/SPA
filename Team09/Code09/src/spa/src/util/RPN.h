#include "util/RPNToken.h"

#include <cctype>
#include <stack>
#include <string>
#include <vector>

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
