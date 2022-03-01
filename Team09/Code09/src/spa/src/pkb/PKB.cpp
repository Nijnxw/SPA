#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"

PKB::PKB() {
}

void PKB::clearAllStores() {
	PKB::entityStore.clear();
	PKB::followsStore.clear();
	PKB::parentStore.clear();
	UsesStore::clear();
	ModifiesStore::clear();
}

/* Setters called by Source Processor */
bool PKB::addProcedure(std::string procedure) {
	return entityStore.addProcedure(procedure);
}

bool PKB::addVariable(std::string variable) {
	return entityStore.addVariable(variable);
}
bool PKB::addConstant(std::string constant) {
	return entityStore.addConstant(constant);
}

bool PKB::addStatementNumber(int statementNumber) {
	return entityStore.addStatementNumber(statementNumber);
}

bool PKB::addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide) {
	return entityStore.addAssignStatement(statementNumber, leftHandSide, rightHandSide);
}

bool PKB::addStatementWithType(EntityType statementType, int statementNumber) {
	return entityStore.addStatementWithType(statementType, statementNumber);
}

bool PKB::addFollows(int follower, int followee) {
	return followsStore.addRelationship(follower, followee);
}

bool PKB::addFollowsT(int follower, int followee) {
	return followsStore.addRelationshipT(follower, followee);
}

bool PKB::addParent(int parent, int child) {
	return parentStore.addRelationship(parent, child);
}

bool PKB::addParentT(int parent, int child) {
	return parentStore.addRelationshipT(parent, child);
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
	return entityStore.getProcedures();
}

std::unordered_set<std::string> PKB::getVariables() {
	return entityStore.getVariables();
}

std::unordered_set<std::string> PKB::getConstants() {
	return entityStore.getConstants();
}

std::unordered_set<int> PKB::getStatementNumbers() {
	return entityStore.getStatementNumbers();
}

std::unordered_map<int, AssignStatement> PKB::getAssignStatements() {
	return entityStore.getAssignStatements();
}

std::unordered_set<int> PKB::getStatementsWithType(EntityType statementType) {
	return entityStore.getStatementsWithType(statementType);
}

/* Follows and Parent Getters */
bool PKB::hasRelationship(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.hasRelationship();
	case RelationRef::PARENT:
		return parentStore.hasRelationship();
	case RelationRef::FOLLOWS_T:
		return followsStore.hasTRelationship();
	case RelationRef::PARENT_T:
		return parentStore.hasTRelationship();
	default:
		return false;
	}
}

bool PKB::isRelationship(RelationRef relationship, int statementOne, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.isRelationship(statementOne, statementTwo);
	case RelationRef::PARENT:
		return parentStore.isRelationship(statementOne, statementTwo);
	case RelationRef::FOLLOWS_T:
		return followsStore.isTRelationship(statementOne, statementTwo);
	case RelationRef::PARENT_T:
		return parentStore.isTRelationship(statementOne, statementTwo);
	default:
		return false;
	}
}

bool PKB::isFirstEntity(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.isFirstStatement(statementOne);
	case RelationRef::PARENT:
		return parentStore.isFirstStatement(statementOne);
	case RelationRef::FOLLOWS_T:
		return followsStore.isFirstStatementT(statementOne);
	case RelationRef::PARENT_T:
		return parentStore.isFirstStatementT(statementOne);
	default:
		return false;
	}
}

bool PKB::isSecondEntity(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.isSecondStatement(statementTwo);
	case RelationRef::PARENT:
		return parentStore.isSecondStatement(statementTwo);
	case RelationRef::FOLLOWS_T:
		return followsStore.isSecondStatementT(statementTwo);
	case RelationRef::PARENT_T:
		return parentStore.isSecondStatementT(statementTwo);
	default:
		return false;
	}
}

std::unordered_set<int> PKB::getFirstEntities(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.getFirstStatements(statementTwo);
	case RelationRef::PARENT:
		return parentStore.getFirstStatements(statementTwo);
	case RelationRef::FOLLOWS_T:
		return followsStore.getFirstStatementsT(statementTwo);
	case RelationRef::PARENT_T:
		return parentStore.getFirstStatementsT(statementTwo);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getSecondEntities(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.getSecondStatements(statementOne);
	case RelationRef::PARENT:
		return parentStore.getSecondStatements(statementOne);
	case RelationRef::FOLLOWS_T:
		return followsStore.getSecondStatementsT(statementOne);
	case RelationRef::PARENT_T:
		return parentStore.getSecondStatementsT(statementOne);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllFirstEntities(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.getAllFirstStatements();
	case RelationRef::PARENT:
		return parentStore.getAllFirstStatements();
	case RelationRef::FOLLOWS_T:
		return followsStore.getAllFirstStatementsT();
	case RelationRef::PARENT_T:
		return parentStore.getAllFirstStatementsT();
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllSecondEntities(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.getAllSecondStatements();
	case RelationRef::PARENT:
		return parentStore.getAllSecondStatements();
	case RelationRef::FOLLOWS_T:
		return followsStore.getAllSecondStatementsT();
	case RelationRef::PARENT_T:
		return parentStore.getAllSecondStatementsT();
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllRelationshipPairs(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return followsStore.getAllRelationshipPairs();
	case RelationRef::PARENT:
		return parentStore.getAllRelationshipPairs();
	case RelationRef::FOLLOWS_T:
		return followsStore.getAllRelationshipTPairs();
	case RelationRef::PARENT_T:
		return parentStore.getAllRelationshipTPairs();
	default:
		std::tuple<std::vector<int>, std::vector<int>> emptyResult;
		return emptyResult;
	}
}

/* Follows Getters */
bool PKB::hasFollowsRelationship() {
	return followsStore.hasRelationship();
}

bool PKB::hasFollowsTRelationship() {
	return followsStore.hasTRelationship();
}

bool PKB::isFollowsRelationship(int follower, int followee) {
	return followsStore.isRelationship(follower, followee);
}

bool PKB::isFollowsTRelationship(int follower, int followee) {
	return followsStore.isTRelationship(follower, followee);
}

bool PKB::isFollower(int follower) {
	return followsStore.isFirstStatement(follower);
}

bool PKB::isFollowee(int followee) {
	return followsStore.isSecondStatement(followee);
}

bool PKB::isFollowerT(int follower) {
	return followsStore.isFirstStatementT(follower);
}

bool PKB::isFolloweeT(int followee) {
	return followsStore.isSecondStatementT(followee);
}

std::unordered_set<int> PKB::getFollowee(int follower) {
	return followsStore.getSecondStatements(follower);
}

std::unordered_set<int> PKB::getFollower(int followee) {
	return followsStore.getFirstStatements(followee);
}

std::unordered_set<int> PKB::getAllFollowees() {
	return followsStore.getAllSecondStatements();
}

std::unordered_set<int> PKB::getAllFollowers() {
	return followsStore.getAllFirstStatements();
}

std::unordered_set<int> PKB::getFolloweesT(int follower) {
	return followsStore.getSecondStatementsT(follower);
}

std::unordered_set<int> PKB::getFollowersT(int followee) {
	return followsStore.getFirstStatementsT(followee);
}

std::unordered_set<int> PKB::getAllFolloweesT() {
	return followsStore.getAllSecondStatementsT();
}

std::unordered_set<int> PKB::getAllFollowersT() {
	return followsStore.getAllFirstStatementsT();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllFollowsPairs() {
	return followsStore.getAllRelationshipPairs();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllFollowsTPairs() {
	return followsStore.getAllRelationshipTPairs();
}

/* Parent Getters */
bool PKB::hasParentRelationship() {
	return parentStore.hasRelationship();
}

bool PKB::hasParentTRelationship() {
	return parentStore.hasTRelationship();
}

bool PKB::isParentRelationship(int parent, int child) {
	return parentStore.isRelationship(parent, child);
}

bool PKB::isParentTRelationship(int parent, int child) {
	return parentStore.isTRelationship(parent, child);
}

bool PKB::isParent(int parent) {
	return parentStore.isFirstStatement(parent);
}

bool PKB::isChild(int child) {
	return parentStore.isSecondStatement(child);
}

bool PKB::isParentT(int parent) {
	return parentStore.isFirstStatementT(parent);
}

bool PKB::isChildT(int child) {
	return parentStore.isSecondStatementT(child);
}

std::unordered_set<int> PKB::getChildren(int parent) {
	return parentStore.getSecondStatements(parent);
}

std::unordered_set<int> PKB::getParent(int child) {
	return parentStore.getFirstStatements(child);
}

std::unordered_set<int> PKB::getAllChildren() {
	return parentStore.getAllSecondStatements();
}

std::unordered_set<int> PKB::getAllParents() {
	return parentStore.getAllFirstStatements();
}

std::unordered_set<int> PKB::getChildrenT(int parent) {
	return parentStore.getSecondStatementsT(parent);
}

std::unordered_set<int> PKB::getParentsT(int child) {
	return parentStore.getFirstStatementsT(child);
}

std::unordered_set<int> PKB::getAllChildrenT() {
	return parentStore.getAllSecondStatementsT();
}

std::unordered_set<int> PKB::getAllParentsT() {
	return parentStore.getAllFirstStatementsT();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentPairs() {
	return parentStore.getAllRelationshipPairs();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentTPairs() {
	return parentStore.getAllRelationshipTPairs();
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

std::unordered_set<std::string> PKB::getVariablesUsedByStatement(int stmtNo) {
	return UsesStore::getVariablesUsedByStatement(stmtNo);
}
std::unordered_set<std::string> PKB::getVariablesUsedByProcedure(const std::string& procName) {
	return UsesStore::getVariablesUsedByProcedure(procName);
}
std::unordered_set<int> PKB::getStatementsUsingVariable(const std::string& variable) {
	return UsesStore::getStatementsUsingVariable(variable);
}
std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getStmtsToUsedVariable(const std::unordered_set<int>& stmts) {
	return UsesStore::getStmtsToUsedVariable(stmts);
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

std::unordered_set<std::string> PKB::getVariablesModifiedByStatement(int stmtNo) {
	return ModifiesStore::getVariablesModifiedByStatement(stmtNo);
}

std::unordered_set<std::string> PKB::getVariablesModifiedByProcedure(const std::string& procName) {
	return ModifiesStore::getVariablesModifiedByProcedure(procName);
}

std::unordered_set<int> PKB::getStatementsModifyingVariable(const std::string& variable) {
	return ModifiesStore::getStatementsModifyingVariable(variable);
}

std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getStmtsToModifiedVariable(const std::unordered_set<int>& stmts) {
	return ModifiesStore::getStmtsToModifiedVariable(stmts);
}
