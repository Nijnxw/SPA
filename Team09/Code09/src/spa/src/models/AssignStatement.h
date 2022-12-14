#pragma once

#include <string>
#include <vector>

#include "./Statement.h"

class AssignStatement : public Statement {
private:
	std::string leftHandSide;
	std::string rightHandSide;

public:
	AssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide);

	std::string getLeftHandSide() const;
	std::string getRightHandSide() const;

	bool operator==(const AssignStatement& otherStmt) const;
};
