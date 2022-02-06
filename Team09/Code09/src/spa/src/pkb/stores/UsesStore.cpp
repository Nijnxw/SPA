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
