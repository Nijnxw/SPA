//TODO: Possible optimisation by early termination given isBooleanResult argument, currently boolean is not used
#include "UsesStore.h"

UsesStore::UsesStore() {}

void UsesStore::clear() {
	usesStatements.clear();
	usedVariables.clear();
	statementNumberToVariablesUsed.clear();
	variableToStatementNumbersUsedBy.clear();
	procedureToVariablesUsed.clear();
	variableToProceduresUsedBy.clear();
}

// ============ GETTER METHODS ==============

std::unordered_set<int> UsesStore::getUsesStatements() {
	return usesStatements;
}
std::unordered_set<std::string> UsesStore::getUsedVariables() {
	return usedVariables;
}
std::unordered_map<int, std::unordered_set<std::string>> UsesStore::getStatementNumberToVariablesUsed() {
	return statementNumberToVariablesUsed;
}
std::unordered_map<std::string, std::unordered_set<int>> UsesStore::getVariableToStatementNumbersUsedBy() {
	return variableToStatementNumbersUsedBy;
}
std::unordered_map<std::string, std::unordered_set<std::string>> UsesStore::getProcedureToVariablesUsed() {
	return procedureToVariablesUsed;
}
std::unordered_map<std::string, std::unordered_set<std::string>> UsesStore::getVariableToProceduresUsedBy() {
	return variableToProceduresUsedBy;
}

// ============ HELPER METHODS ==============

/* Get variables used by statement */
std::unordered_set<std::string> UsesStore::getVariablesUsedByStatement(int stmtNo) {
	if (!getStatementNumberToVariablesUsed().count(stmtNo))
		return {};
	return getStatementNumberToVariablesUsed().at(stmtNo);
}

/* Get variables used by procedure */
std::unordered_set<std::string> UsesStore::getVariablesUsedByProcedure(const std::string& procName) {
	if (!getProcedureToVariablesUsed().count(procName))
		return {};
	return getProcedureToVariablesUsed().at(procName);
}

/* Get statements using a particular variable */
std::unordered_set<int> UsesStore::getStatementsUsingVariable(const std::string& variable) {
	if (!getVariableToStatementNumbersUsedBy().count(variable))
		return {};
	return getVariableToStatementNumbersUsedBy().at(variable);
}

/* Returns a mapping of each statement in the input statement set to the variables its using.
	Mapping is represented as a tuple of vectors to preserve ordering */
std::tuple<std::vector<std::string>, std::vector<std::string>>
UsesStore::getStmtsToUsedVariable(const std::unordered_set<int>& stmts) {
	std::vector<std::string> resultStmts;
	std::vector<std::string> resultVars;
	for (int stmt : stmts) {
		for (const std::string& var : getVariablesUsedByStatement(stmt)) {
			resultStmts.push_back(std::to_string(stmt));
			resultVars.push_back(var);
		}
	}
	return { resultStmts, resultVars };
}

// ============ STORE METHODS ==============

/* Add Uses(stmt, var) relationship to PKB */
bool UsesStore::addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	usesStatements.insert(statementNumber);

	if (!statementNumberToVariablesUsed.emplace(statementNumber, variables).second) {
		statementNumberToVariablesUsed.at(statementNumber).insert(variables.begin(), variables.end());
	}

	for (const std::string& v: variables) {
		if (!variableToStatementNumbersUsedBy.emplace(v, std::unordered_set<int>{statementNumber}).second) {
			variableToStatementNumbersUsedBy.at(v).insert(statementNumber);
		}
		usedVariables.insert(v);
	}

	return true;
}

/* Add Uses(proc, var) relationship to PKB */
bool UsesStore::addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {

	if (!procedureToVariablesUsed.emplace(procedure, variables).second) {
		procedureToVariablesUsed.at(procedure).insert(variables.begin(), variables.end());
	}

	for (const std::string& v: variables) {
		if (!variableToProceduresUsedBy.emplace(v, std::unordered_set<std::string>{procedure}).second) {
			variableToProceduresUsedBy.at(v).emplace(procedure);
		}
	}

	return true;
}
