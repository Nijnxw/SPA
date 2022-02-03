#include "util/RPNToken.h"

#include <cctype>
#include <stack>
#include <string>
#include <vector>

class RPN {

private:
    RPN() {};
    static std::vector<RPNToken> convertToRpn(std::string);

public:
    //static std::string convertToRpn(std::string);
    static bool contains(std::string, std::string);
};
