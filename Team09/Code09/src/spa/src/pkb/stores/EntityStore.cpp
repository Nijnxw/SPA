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

	assignStatementsToStructs.clear();
	ifStatementsToConditionalVariables.clear();
	whileStatementsToConditionalVariables.clear();
	callStatementsToProcedures.clear();
	printStatementsToVariables.clear();
	readStatementsToVariables.clear();
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
	return callStatements.insert(statementNumber).second && callStatementsToProcedures.insert({ statementNumber, procedure }).second;
}

bool EntityStore::addReadStatement(int statementNumber, const std::string& variable) {
	return readStatements.insert(statementNumber).second && readStatementsToVariables.insert({ statementNumber, variable }).second;
}

bool EntityStore::addPrintStatement(int statementNumber, const std::string& variable) {
	return printStatements.insert(statementNumber).second && printStatementsToVariables.insert({ statementNumber, variable }).second;
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
	std::unordered_set<int> statements;

	switch (statementType) {
	case EntityType::ASSIGN:
		statements = assignStatements;
		break;
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