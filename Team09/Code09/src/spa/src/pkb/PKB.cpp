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

/* Setters called by Query Evaluator */
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

/* Uses Getters */
std::unordered_set<int> PKB::getUsesStatements() {
	return UsesStore::getUsesStatements();
}

std::unordered_set<std::string> PKB::getUsedVariables() {
	return UsesStore::getUsedVariables();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getStatementNumberToVariablesUsed() {
	return UsesStore::getStatementNumberToVariablesUsed();
}

std::unordered_map<std::string, std::unordered_set<int>> PKB::getVariableToStatementNumbersUsedBy() {
	return UsesStore::getVariableToStatementNumbersUsedBy();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getProcedureToVariablesUsed() {
	return UsesStore::getProcedureToVariablesUsed();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getVariableToProceduresUsedBy() {
	return UsesStore::getVariableToProceduresUsedBy();
}

/* Modifies Getters */
std::unordered_set<int> PKB::getModifiesStatements() {
	return ModifiesStore::getModifiesStatements();
}

std::unordered_set<std::string> PKB::getModifiedVariables() {
	return ModifiesStore::getModifiedVariables();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getStatementNumberToVariablesModified() {
	return ModifiesStore::getStatementNumberToVariablesModified();
}

std::unordered_map<std::string, std::unordered_set<int>> PKB::getVariableToStatementNumbersModifiedBy() {
	return ModifiesStore::getVariableToStatementNumbersModifiedBy();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getProcedureToVariablesModified() {
	return ModifiesStore::getProcedureToVariablesModified();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getVariableToProceduresModifiedBy() {
	return ModifiesStore::getVariableToProceduresModifiedBy();
}
