#include "EntityStore.h"

EntityStore::EntityStore() {}

void EntityStore::clear() {
	procedures.clear();
	variables.clear();
	constants.clear();
	statements.clear();
	assignStatements.clear();
	ifStatements.clear();
	whileStatements.clear();
	callStatements.clear();
	printStatements.clear();
	readStatements.clear();
	readVariables.clear();
	printVariables.clear();

	assignStatementsToStructs.clear();
	ifStatementsToConditionalVariables.clear();
	whileStatementsToConditionalVariables.clear();
	callStatementsToProcedures.clear();
	printStatementsToVariables.clear();
	readStatementsToVariables.clear();
	proceduresToCallStatements.clear();
	variablesToPrintStatements.clear();
	variablesToReadStatements.clear();
}

bool EntityStore::addProcedure(const std::string& procedure) {
	return procedures.insert(procedure).second;
}

bool EntityStore::addVariable(const std::string& variable) {
	return variables.insert(variable).second;
}

bool EntityStore::addConstant(const std::string& constant) {
	return constants.insert(constant).second;
}

bool EntityStore::addStatementNumber(int statementNumber) {
	return statements.insert(statementNumber).second;
}

bool EntityStore::addAssignStatement(int statementNumber, const std::string& leftHandSide, const std::string& rightHandSide) {
	AssignStatement assignStatement(statementNumber, leftHandSide, rightHandSide);
	return assignStatements.insert(statementNumber).second && assignStatementsToStructs.insert({ statementNumber, assignStatement }).second;
}

bool EntityStore::addIfStatement(int statementNumber, const std::unordered_set<std::string>& conditionalVariables) {
	return ifStatements.insert(statementNumber).second && ifStatementsToConditionalVariables.insert({ statementNumber, conditionalVariables }).second;
}

bool EntityStore::addWhileStatement(int statementNumber, const std::unordered_set<std::string>& conditionalVariables) {
	return whileStatements.insert(statementNumber).second && whileStatementsToConditionalVariables.insert({ statementNumber, conditionalVariables }).second;
}

bool EntityStore::addCallStatement(int statementNumber, const std::string& procedure) {
	bool isSuccess = callStatements.insert(statementNumber).second;
	if (isSuccess) {
		isSuccess = callStatementsToProcedures.insert({ statementNumber, procedure }).second;
	}
	if (isSuccess) {
		if (!proceduresToCallStatements.emplace(procedure, std::unordered_set<std::string>{std::to_string(statementNumber)}).second) {
			isSuccess = proceduresToCallStatements.at(procedure).insert(std::to_string(statementNumber)).second;
		}
	}
	return isSuccess;
}

bool EntityStore::addReadStatement(int statementNumber, const std::string& variable) {
	bool isSuccess = readStatements.insert(statementNumber).second;
	if (isSuccess) {
		isSuccess = readStatementsToVariables.insert({ statementNumber, variable }).second;
	}
	if (isSuccess) {
		isSuccess = readVariables.insert(variable).second;
	}
	if (isSuccess) {
		if (!variablesToReadStatements.emplace(variable, std::unordered_set<std::string>{std::to_string(statementNumber)}).second) {
			isSuccess = variablesToReadStatements.at(variable).insert(std::to_string(statementNumber)).second;
		}
	}
	return isSuccess;
}

bool EntityStore::addPrintStatement(int statementNumber, const std::string& variable) {
	bool isSuccess = printStatements.insert(statementNumber).second;
	if (isSuccess) {
		isSuccess = printStatementsToVariables.insert({ statementNumber, variable }).second;
	}
	if (isSuccess) {
		isSuccess = printVariables.insert(variable).second;
	}
	if (isSuccess) {
		if (!variablesToPrintStatements.emplace(variable, std::unordered_set<std::string>{std::to_string(statementNumber)}).second) {
			isSuccess = variablesToPrintStatements.at(variable).insert(std::to_string(statementNumber)).second;
		}
	}
	return isSuccess;
}

std::unordered_set<std::string> EntityStore::getProcedures() {
	return procedures;
}

std::unordered_set<std::string> EntityStore::getVariables() {
	return variables;
}

std::unordered_set<std::string> EntityStore::getConstants() {
	return constants;
}

std::unordered_set<int> EntityStore::getStatementNumbers() {
	return statements;
}

std::unordered_set<int> EntityStore::getStatementsWithType(EntityType statementType) {
	std::unordered_set<int> statementsWithType;

	switch (statementType) {
	case EntityType::STMT:
		statementsWithType = statements;
		break;
	case EntityType::ASSIGN:
		statementsWithType = assignStatements;
		break;
	case EntityType::IF:
		statementsWithType = ifStatements;
		break;
	case EntityType::WHILE:
		statementsWithType = whileStatements;
		break;
	case EntityType::CALL:
		statementsWithType = callStatements;
		break;
	case EntityType::PRINT:
		statementsWithType = printStatements;
		break;
	case EntityType::READ:
		statementsWithType = readStatements;
		break;
	default:
		break;
	}

	return statementsWithType;
}

std::unordered_set<std::string> EntityStore::getPrintVariables() {
	return printVariables;
}

std::unordered_set<std::string> EntityStore::getReadVariables() {
	return readVariables;
}

std::unordered_map<int, AssignStatement> EntityStore::getAssignStatementsToStructs() {
	return assignStatementsToStructs;
}

std::unordered_map<int, std::unordered_set<std::string>> EntityStore::getIfStatementsToConditionalVariables() {
	return ifStatementsToConditionalVariables;
}

std::unordered_map<int, std::unordered_set<std::string>> EntityStore::getWhileStatementsToConditionalVariables() {
	return whileStatementsToConditionalVariables;
}

std::unordered_map<int, std::string> EntityStore::getCallStatementsToProcedures() {
	return callStatementsToProcedures;
}

std::unordered_map<int, std::string> EntityStore::getPrintStatementsToVariables() {
	return printStatementsToVariables;
}

std::unordered_map<int, std::string> EntityStore::getReadStatementsToVariables() {
	return readStatementsToVariables;
}

std::unordered_map<std::string, std::unordered_set<std::string>> EntityStore::getProceduresToCallStatements() {
	return proceduresToCallStatements;
}

std::unordered_map<std::string, std::unordered_set<std::string>> EntityStore::getVariablesToPrintStatements() {
	return variablesToPrintStatements;
}

std::unordered_map<std::string, std::unordered_set<std::string>> EntityStore::getVariablesToReadStatements() {
	return variablesToReadStatements;
}