#include "EntityStore.h"

std::unordered_set<std::string> EntityStore::procedures;
std::unordered_set<std::string> EntityStore::variables;
std::unordered_set<std::string> EntityStore::constants;
std::unordered_set<int> EntityStore::statements;

std::unordered_map<int, AssignStatement> EntityStore::assignStatements;
std::unordered_set<int> EntityStore::ifStatements;
std::unordered_set<int> EntityStore::whileStatements;
std::unordered_set<int> EntityStore::callStatements;
std::unordered_set<int> EntityStore::printStatements;
std::unordered_set<int> EntityStore::readStatements;

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

bool EntityStore::addStatement(EntityType statementType, int statementNumber) {
	bool resultValue = true;

	switch (statementType) {
	case EntityType::IF:
		resultValue = ifStatements.emplace(statementNumber).second;
		break;
	case EntityType::WHILE:
		resultValue = whileStatements.emplace(statementNumber).second;
		break;
	case EntityType::CALL:
		resultValue = callStatements.emplace(statementNumber).second;
		break;
	case EntityType::PRINT:
		resultValue = printStatements.emplace(statementNumber).second;
		break;
	case EntityType::READ:
		resultValue = readStatements.emplace(statementNumber).second;
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

std::unordered_set<int> EntityStore::getStatements() {
	return statements;
}

std::unordered_map<int, AssignStatement> EntityStore::getAssignStatements() {
	return assignStatements;
}

std::unordered_set<int> EntityStore::getIfStatements() {
	return ifStatements;
}

std::unordered_set<int> EntityStore::getWhileStatements() {
	return whileStatements;
}

std::unordered_set<int> EntityStore::getCallStatements() {
	return callStatements;
}

std::unordered_set<int> EntityStore::getPrintStatements() {
	return printStatements;
}

std::unordered_set<int> EntityStore::getReadStatements() {
	return readStatements;
}

