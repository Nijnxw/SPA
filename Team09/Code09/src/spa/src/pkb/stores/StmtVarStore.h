#pragma once

#include "pkb/stores/Store.h"

class StmtVarStore : public Store {
protected:
	std::unordered_set<int> stmtInRelationship;
	std::unordered_set<std::string> varInRelationship;
	std::unordered_map<int, std::unordered_set<std::string>> stmtToVarRelationship;
	std::unordered_map<std::string, std::unordered_set<int>> varToStmtRelationship;

public:
	/* Getters called by QE */
	std::unordered_set<int> getStmtInRelationship();
	std::unordered_set<std::string> getVarInRelationship();
	std::unordered_map<int, std::unordered_set<std::string>> getStmtToVarRelationship();
	std::unordered_map<std::string, std::unordered_set<int>> getVarToStmtRelationship();

	std::unordered_set<std::string> getVarByStmt(int stmtNo);
	std::unordered_set<int> getStmtByVar(const std::string& variable);
	std::tuple<std::vector<std::string>, std::vector<std::string>> getStmtToVarByStmts(const std::unordered_set<int>& stmts);

	/* Setters called by DE */
	bool addStmtVarRelationship(int statementNumber, const std::unordered_set<std::string>& variables);
};
