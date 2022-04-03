#include "StmtVarStore.h"

// ============ GETTER METHODS ==============

std::unordered_set<int> StmtVarStore::getStmtInRelationship() {
	return stmtInRelationship;
}

std::unordered_set<std::string> StmtVarStore::getVarInRelationship() {
	return varInRelationship;
}

std::unordered_map<int, std::unordered_set<std::string>> StmtVarStore::getStmtToVarRelationship() {
	return stmtToVarRelationship;
}

std::unordered_map<std::string, std::unordered_set<int>> StmtVarStore::getVarToStmtRelationship() {
	return varToStmtRelationship;
}

// ============ HELPER METHODS ==============

std::unordered_set<std::string> StmtVarStore::getVarByStmt(int stmtNo) {
	if (!stmtToVarRelationship.count(stmtNo)) {
		return {};
	}
	return stmtToVarRelationship.at(stmtNo);
}

std::unordered_set<int> StmtVarStore::getStmtByVar(const std::string& variable) {
	if (!varToStmtRelationship.count(variable)) {
		return {};
	}
	return varToStmtRelationship.at(variable);
}

// Given a set of stmt numbers, generate a map of all stmt -> var relationships
std::tuple<std::vector<std::string>, std::vector<std::string>>
StmtVarStore::getStmtToVarByStmts(const std::unordered_set<int>& stmts) {
	std::vector<std::string> resultStmts;
	std::vector<std::string> resultVars;
	for (int stmt : stmts) {
		for (const std::string& var : getVarByStmt(stmt)) {
			resultStmts.push_back(std::to_string(stmt));
			resultVars.push_back(var);
		}
	}
	return { resultStmts, resultVars };
}

// ============ STORE METHODS ==============

bool StmtVarStore::addStmtVarRelationship(int statementNumber, const std::unordered_set<std::string>& variables) {
	stmtInRelationship.insert(statementNumber);
	stmtToVarRelationship[statementNumber].insert(variables.begin(), variables.end());

	for (const std::string& v : variables) {
		varToStmtRelationship[v].emplace(statementNumber);
		varInRelationship.insert(v);
	}
	
	return true;
}
