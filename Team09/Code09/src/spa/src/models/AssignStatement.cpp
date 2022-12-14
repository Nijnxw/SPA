#include "AssignStatement.h"

AssignStatement::AssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide)
	: Statement(statementNumber) {
	this->leftHandSide = leftHandSide;
	this->rightHandSide = rightHandSide;
}

std::string AssignStatement::getLeftHandSide() const {
	return leftHandSide;
}

std::string AssignStatement::getRightHandSide() const {
	return rightHandSide;
}

bool AssignStatement::operator==(const AssignStatement& otherStmt) const {
	return (statementNumber == otherStmt.statementNumber) &&
		   (leftHandSide == otherStmt.leftHandSide) &&
		   (rightHandSide == otherStmt.rightHandSide);
}