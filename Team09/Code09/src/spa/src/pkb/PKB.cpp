#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"

PKB::PKB() {}

void PKB::clearAllStores() {
	EntityStore::clear();
	FollowsStore::clear();
	ParentStore::clear();
	UsesStore::clear();
	ModifiesStore::clear();
}

/* Getters called by Source Processor */
bool addProcedure(std::string procedure) {
	return EntityStore::addProcedure(procedure);
}

bool addVariable(std::string variable) {
	return EntityStore::addVariable(variable);
}
bool addConstant(std::string constant) {
	return EntityStore::addConstant(constant);
}

bool addStatementNumber(int statementNumber) {
	return EntityStore::addStatementNumber(statementNumber);
}

bool addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide) {
	return EntityStore::addAssignStatement(statementNumber, leftHandSide, rightHandSide);
}

bool addStatement(EntityType statementType, int statementNumber) {
	return EntityStore::addStatement(statementType, statementNumber);
}

/* bool addFollows(int follower, int followee);
bool addFollowsT(int follower, int followee);
bool addParent(int parent, int child);
bool addParentT(int parent, int child);
bool addUsesStatement(int statementNumber, EntityType statementType, std::unordered_set<std::string> variables);
bool addUsesProcedure(std::string procedure, EntityType statementType, std::unordered_set<std::string> variables);
bool addModifiesStatement(int statementNumber, EntityType statementType, std::unordered_set<std::string> variables);
bool addModifiesProcedure(std::string procedure, EntityType statementType, std::unordered_set<std::string> variables); */

/* Setters called by Query Evaluator */
std::unordered_set<std::string> getAllProcedures();
std::unordered_set<std::string> getAllVariables();
std::unordered_set<std::string> getAllConstants();
std::unordered_set<int> getAllStatements();

std::unordered_set<int> getAllAssignStatements();
std::unordered_set<int> getAllStatements(EntityType statementType);
