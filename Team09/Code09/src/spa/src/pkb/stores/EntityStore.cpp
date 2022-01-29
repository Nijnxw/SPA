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

bool EntityStore::addProcedure(std::string procedure) {
	return procedures.emplace(procedure).second;
}

bool EntityStore::addVariable(std::string variable) {
	return variables.emplace(variable).second;
}

bool EntityStore::addConstant(std::string constant) {
	return constants.emplace(constant).second;
}

bool EntityStore::addStatementNumber(int statementNumber) {
	return statements.emplace(statementNumber).second;
}

bool EntityStore::addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide) {
	AssignStatement assignStatement(statementNumber, leftHandSide, rightHandSide);
	return assignStatements.emplace(statementNumber, assignStatement).second;
}

bool EntityStore::addStatement(StatementType statementType, int statementNumber) {
	bool resultValue = true;

	switch (statementType) {
	case IF:
		resultValue = ifStatements.emplace(statementNumber).second;
		break;
	case WHILE:
		resultValue = whileStatements.emplace(statementNumber).second;
		break;
	case CALL:
		resultValue = callStatements.emplace(statementNumber).second;
		break;
	case PRINT:
		resultValue = printStatements.emplace(statementNumber).second;
		break;
	case READ:
		resultValue = readStatements.emplace(statementNumber).second;
		break;
	}

	return resultValue;
}