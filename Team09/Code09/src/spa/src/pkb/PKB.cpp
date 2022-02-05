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

/* Setters called by Source Processor */
bool PKB::addProcedure(std::string procedure) {
	return EntityStore::addProcedure(procedure);
}

bool PKB::addVariable(std::string variable) {
	return EntityStore::addVariable(variable);
}
bool PKB::addConstant(std::string constant) {
	return EntityStore::addConstant(constant);
}

bool PKB::addStatementNumber(int statementNumber) {
	return EntityStore::addStatementNumber(statementNumber);
}

bool PKB::addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide) {
	return EntityStore::addAssignStatement(statementNumber, leftHandSide, rightHandSide);
}

bool PKB::addStatementWithType(EntityType statementType, int statementNumber) {
	return EntityStore::addStatementWithType(statementType, statementNumber);
}

bool PKB::addFollows(int follower, int followee) {
	return FollowsStore::addFollows(follower, followee);
}

bool PKB::addFollowsT(int follower, int followee) {
	return FollowsStore::addFollowsT(follower, followee);
}

bool PKB::addParent(int parent, int child) {
	return ParentStore::addParent(parent, child);
}

bool PKB::addParentT(int parent, int child) {
	return ParentStore::addParentT(parent, child);
}

bool PKB::addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	return UsesStore::addUsesStatement(statementNumber, variables);
}

bool PKB::addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	return UsesStore::addUsesProcedure(procedure, variables);
}

bool PKB::addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	return ModifiesStore::addModifiesStatement(statementNumber, variables);
}
bool PKB::addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	return ModifiesStore::addModifiesProcedure(procedure, variables);
}

/* Getters called by Query Evaluator */
std::unordered_set<std::string> PKB::getProcedures() {
	return EntityStore::getProcedures();
}

std::unordered_set<std::string> PKB::getVariables() {
	return EntityStore::getVariables();
}

std::unordered_set<std::string> PKB::getConstants() {
	return EntityStore::getConstants();
}

std::unordered_set<int> PKB::getStatementNumbers() {
	return EntityStore::getStatementNumbers();
}

std::unordered_map<int, AssignStatement> PKB::getAssignStatements() {
	return EntityStore::getAssignStatements();
}

std::unordered_set<int> PKB::getStatementsWithType(EntityType statementType) {
	return EntityStore::getStatementsWithType(statementType);
}

QueryClauseTable PKB::getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return FollowsStore::getFollows(LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable PKB::getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return FollowsStore::getFollowsT(LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable PKB::getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return ParentStore::getParent(LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable PKB::getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return ParentStore::getParentT(LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable PKB::getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return UsesStore::getUses(LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable PKB::getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return ModifiesStore::getModifies(LHS, RHS, LHSType, RHSType, isBooleanResult);
}
