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
	return assignStatements.emplace(statementNumber, assignStatement).second;
}

bool EntityStore::addStatementWithType(EntityType statementType, int statementNumber) {
	bool resultValue = true;

	switch (statementType) {
	case EntityType::IF:
		resultValue = ifStatements.insert(statementNumber).second;
		break;
	case EntityType::WHILE:
		resultValue = whileStatements.insert(statementNumber).second;
		break;
	case EntityType::CALL:
		resultValue = callStatements.insert(statementNumber).second;
		break;
	case EntityType::PRINT:
		resultValue = printStatements.insert(statementNumber).second;
		break;
	case EntityType::READ:
		resultValue = readStatements.insert(statementNumber).second;
		break;
	default:
		break;
	}

	return resultValue;
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

std::unordered_map<int, AssignStatement> EntityStore::getAssignStatements() {
	return assignStatements;
}

std::unordered_set<int> EntityStore::getStatementsWithType(EntityType statementType) {
	std::unordered_set<int> statements;

	switch (statementType) {
	case EntityType::IF:
		statements = ifStatements;
		break;
	case EntityType::WHILE:
		statements = whileStatements;
		break;
	case EntityType::CALL:
		statements = callStatements;
		break;
	case EntityType::PRINT:
		statements = printStatements;
		break;
	case EntityType::READ:
		statements = readStatements;
		break;
	default:
		break;
	}

	return statements;
}

