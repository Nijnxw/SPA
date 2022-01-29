#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <models/AssignStatement.h>

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

	static bool addProcedure(std::string procedure);
	static bool addVariable(std::string variable);
	static bool addConstant(std::string constant);
	static bool addStatementNumber(int statementNumber);

	static bool addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide);
	static bool addStatement(StatementType statementType, int statementNumber);
}