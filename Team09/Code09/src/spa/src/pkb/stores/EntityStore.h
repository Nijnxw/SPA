#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <models/AssignStatement.h>
#include <models/EntityType.h>

class EntityStore {
private:
	static std::unordered_set<std::string> procedures;
	static std::unordered_set<std::string> variables;
	static std::unordered_set<std::string> constants;
	static std::unordered_set<int> statements;

	static std::unordered_map<int, AssignStatement> assignStatements;
	static std::unordered_set<int> ifStatements;
	static std::unordered_set<int> whileStatements;
	static std::unordered_set<int> callStatements;
	static std::unordered_set<int> printStatements;
	static std::unordered_set<int> readStatements;

public:
	EntityStore();

	static void clear();

	/* Setters called by SP and DE */
	static bool addProcedure(const std::string& procedure);
	static bool addVariable(const std::string& variable);
	static bool addConstant(const std::string& constant);
	static bool addStatementNumber(int statementNumber);
	static bool addAssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide);
	static bool addStatementWithType(EntityType statementType, int statementNumber);

	/* Getters called by QE */
	static std::unordered_set<std::string> getProcedures();
	static std::unordered_set<std::string> getVariables();
	static std::unordered_set<std::string> getConstants();
	static std::unordered_set<int> getStatementNumbers();
	static std::unordered_map<int, AssignStatement> getAssignStatements();
	static std::unordered_set<int> getStatementsWithType(EntityType statementType);
};