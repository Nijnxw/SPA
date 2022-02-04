#include "AssignStatement.h"

AssignStatement::AssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide) 
				: statementNumber(statementNumber), leftHandSide(leftHandSide), rightHandSide(rightHandSide) {}

int AssignStatement::getStatementNumber() {
	return statementNumber;
}

std::string AssignStatement::getLeftHandSide() {
	return leftHandSide;
}

std::string AssignStatement::getRightHandSide() {
	return rightHandSide;
}