#include "StmtVarStore.h"

void StmtVarStore::clear() {
	stmtInRelationship.clear();
	procInRelationship.clear();
	varInRelationship.clear();
	stmtToVarRelationship.clear();
	varToStmtRelationship.clear();
	procToVarRelationship.clear();
	varToProcRelationship.clear();
} 

// ============ GETTER METHODS ==============

std::unordered_set<int> StmtVarStore::getStmtInRelationship() {
	return stmtInRelationship;
}
std::unordered_set<std::string> StmtVarStore::getProcInRelationship() {
	return procInRelationship;
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
std::unordered_map<std::string, std::unordered_set<std::string>> StmtVarStore::getProcToVarRelationship() {
	return procToVarRelationship;
}
std::unordered_map<std::string, std::unordered_set<std::string>> StmtVarStore::getVarToProcRelationship() {
	return varToProcRelationship;
}

// ============ HELPER METHODS ==============

std::unordered_set<std::string> StmtVarStore::getVarByStmt(int stmtNo) {
	if (!getStmtToVarRelationship().count(stmtNo)) {
		return {};
	}
	return getStmtToVarRelationship().at(stmtNo);
}

std::unordered_set<std::string> StmtVarStore::getVarByProc(const std::string& procName) {
	if (!getProcToVarRelationship().count(procName)) {
		return {};
	}
	return getProcToVarRelationship().at(procName);
}

std::unordered_set<int> StmtVarStore::getStmtByVar(const std::string& variable) {
	if (!getVarToStmtRelationship().count(variable)) {
		return {};
	}
	return getVarToStmtRelationship().at(variable);
}

std::unordered_set<std::string> StmtVarStore::getProcByVar(const std::string& variable) {
	if (!getVarToProcRelationship().count(variable)) {
		return {};
	}
	return getVarToProcRelationship().at(variable);
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

std::tuple<std::vector<std::string>, std::vector<std::string>>
StmtVarStore::getProcToVarByProcs(const std::unordered_set<std::string>& procs) {
	std::vector<std::string> resultProcs;
	std::vector<std::string> resultVars;
	for (std::string proc : procs) {
		for (const std::string& var : getVarByProc(proc)) {
			resultProcs.push_back(proc);
			resultVars.push_back(var);
		}
	}
	return { resultProcs, resultVars };
}

// ============ STORE METHODS ==============

bool StmtVarStore::addStmtVarRelationship(int statementNumber, const std::unordered_set<std::string>& variables) {
	stmtInRelationship.insert(statementNumber);

	if (!stmtToVarRelationship.emplace(statementNumber, variables).second) {
		stmtToVarRelationship.at(statementNumber).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!varToStmtRelationship.emplace(v, std::unordered_set<int>{statementNumber}).second) {
			varToStmtRelationship.at(v).insert(statementNumber);
		}
		varInRelationship.insert(v);
	}

	return true;
}

bool StmtVarStore::addProcVarRelationship(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	procInRelationship.insert(procedure);

	if (!procToVarRelationship.emplace(procedure, variables).second) {
		procToVarRelationship.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v : variables) {
		if (!varToProcRelationship.emplace(v, std::unordered_set<std::string>{procedure}).second) {
			varToProcRelationship.at(v).emplace(procedure);
		}
	}

	return true;
}
