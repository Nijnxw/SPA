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

	std::unordered_set<int> assignStatements;
	std::unordered_set<int> ifStatements;
	std::unordered_set<int> whileStatements;
	std::unordered_set<int> callStatements;
	std::unordered_set<int> printStatements;
	std::unordered_set<int> readStatements;

	std::unordered_set<std::string> printVariables;
	std::unordered_set<std::string> readVariables;

	std::unordered_map<int, AssignStatement> assignStatementsToStructs;
	std::unordered_map<int, std::unordered_set<std::string>> ifStatementsToConditionalVariables;
	std::unordered_map<int, std::unordered_set<std::string>> whileStatementsToConditionalVariables;
	std::unordered_map<int, std::string> callStatementsToProcedures;
	std::unordered_map<int, std::string> printStatementsToVariables;
	std::unordered_map<int, std::string> readStatementsToVariables;
	std::unordered_map<std::string, std::unordered_set<std::string>> proceduresToCallStatements;
	std::unordered_map<std::string, std::unordered_set<std::string>> variablesToPrintStatements;
	std::unordered_map<std::string, std::unordered_set<std::string>> variablesToReadStatements;

public:
	EntityStore();

	void clear();

	/* Setters called by SP and DE */
	bool addProcedure(const std::string& procedure);
	bool addVariable(const std::string& variable);
	bool addConstant(const std::string& constant);
	bool addStatementNumber(int statementNumber);
	bool addAssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide);
	bool addIfStatement(int statementNumber, const std::unordered_set<std::string>& conditionalVariables);
	bool addWhileStatement(int statementNumber, const std::unordered_set<std::string>& conditionalVariables);
	bool addCallStatement(int statementNumber, const std::string& procedure);
	bool addReadStatement(int statementNumber, const std::string& variable);
	bool addPrintStatement(int statementNumber, const std::string& variable);

	/* Getters called by QE */
	std::unordered_set<std::string> getProcedures();
	std::unordered_set<std::string> getVariables();
	std::unordered_set<std::string> getConstants();
	std::unordered_set<int> getStatementNumbers();
	std::unordered_set<int> getStatementsWithType(EntityType statementType); // For getting statement numbers of a specific statement type.

	std::unordered_set<std::string> getPrintVariables();
	std::unordered_set<std::string> getReadVariables();
	std::unordered_map<int, AssignStatement> getAssignStatementsToStructs();
	std::unordered_map<int, std::unordered_set<std::string>> getIfStatementsToConditionalVariables();
	std::unordered_map<int, std::unordered_set<std::string>> getWhileStatementsToConditionalVariables();
	std::unordered_map<int, std::string> getCallStatementsToProcedures();
	std::unordered_map<int, std::string> getPrintStatementsToVariables();
	std::unordered_map<int, std::string> getReadStatementsToVariables();
	std::unordered_map<std::string, std::unordered_set<std::string>> getProceduresToCallStatements();
	std::unordered_map<std::string, std::unordered_set<std::string>> getVariablesToPrintStatements();
	std::unordered_map<std::string, std::unordered_set<std::string>> getVariablesToReadStatements();

	bool isAssignStmt(int stmtNum);
};