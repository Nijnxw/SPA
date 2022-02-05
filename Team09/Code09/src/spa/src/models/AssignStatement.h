#pragma once

#include <string>
#include <vector>

class AssignStatement {
private:
	int statementNumber;
	std::string leftHandSide;
	std::string rightHandSide;

public:
	AssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide); 

	int getStatementNumber();
	std::string getLeftHandSide();
	std::string getRightHandSide();

	bool operator==(const AssignStatement& otherStmt) const;
};
