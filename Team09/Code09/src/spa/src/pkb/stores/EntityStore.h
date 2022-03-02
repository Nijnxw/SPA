#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../models/AssignStatement.h"
#include "../../models/EntityType.h"

#include "Store.h"

class EntityStore : public Store {
private:
	std::unordered_set<std::string> procedures;
	std::unordered_set<std::string> variables;
	std::unordered_set<std::string> constants;
	std::unordered_set<int> statements;

	std::unordered_map<int, AssignStatement> assignStatements;
	std::unordered_set<int> ifStatements;
	std::unordered_set<int> whileStatements;
	std::unordered_set<int> callStatements;
	std::unordered_set<int> printStatements;
	std::unordered_set<int> readStatements;

public:
	EntityStore();

	void clear();

	/* Setters called by SP and DE */
	bool addProcedure(const std::string& procedure);
	bool addVariable(const std::string& variable);
	bool addConstant(const std::string& constant);
	bool addStatementNumber(int statementNumber);
	bool addAssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide);
	bool addStatementWithType(EntityType statementType, int statementNumber);

	/* Getters called by QE */
	std::unordered_set<std::string> getProcedures();
	std::unordered_set<std::string> getVariables();
	std::unordered_set<std::string> getConstants();
	std::unordered_set<int> getStatementNumbers();
	std::unordered_map<int, AssignStatement> getAssignStatements();
	std::unordered_set<int> getStatementsWithType(EntityType statementType);
};