#include "RPN.h"

//constructor
RPN::RPN(std::string equation) {
	eqn = equation;
	rpn = convertToRpn(eqn);
}

//getters
std::string RPN::getRpnNotation() const {
	return rpn;
}

std::string RPN::getInfixNotation() const {
	return eqn;
}

//check if this rpn contains the other rpn
bool RPN::contains(RPN other) {
	//TO DO
	return true;
}

std::vector<std::string> tokenize(std::string exp) {
	std::vector<std::string> tokens;
	
	return tokens;
}

//takes in equation in infix notation and returns RPN notation
std::string RPN::convertToRpn(std::string infix) {
	return "test";
}
