#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"

PKB::PKB() {}

void PKB::clearAllStores() {
	PKB::entityStore.clear();
	PKB::followsStore.clear();
	PKB::parentStore.clear();
	PKB::usesStore.clear();
	PKB::modifiesStore.clear();
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
	return usesStore.addStmtVarRelationship(statementNumber, variables);
}

bool PKB::addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	return usesStore.addProcVarRelationship(procedure, variables);
}

bool PKB::addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables) {
	return modifiesStore.addStmtVarRelationship(statementNumber, variables);
}
bool PKB::addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables) {
	return modifiesStore.addProcVarRelationship(procedure, variables);
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

/* Follows and Parent Getters */
bool PKB::hasRelationship(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::hasFollowsRelationship();
	case RelationRef::PARENT:
		return ParentStore::hasParentRelationship();
	case RelationRef::FOLLOWS_T:
		return FollowsStore::hasFollowsTRelationship();
	case RelationRef::PARENT_T:
		return ParentStore::hasParentTRelationship();
	default:
		return false;
	}
}

bool PKB::isRelationship(RelationRef relationship, int statementOne, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFollowsRelationship(statementOne, statementTwo);
	case RelationRef::PARENT:
		return ParentStore::isParentRelationship(statementOne, statementTwo);
	case RelationRef::FOLLOWS_T:
		return FollowsStore::isFollowsTRelationship(statementOne, statementTwo);
	case RelationRef::PARENT_T:
		return ParentStore::isParentTRelationship(statementOne, statementTwo);
	default:
		return false;
	}
}

bool PKB::isFirstEntity(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFollower(statementOne);
	case RelationRef::PARENT:
		return ParentStore::isParent(statementOne);
	case RelationRef::FOLLOWS_T:
		return FollowsStore::isFollowerT(statementOne);
	case RelationRef::PARENT_T:
		return ParentStore::isParentT(statementOne);
	default:
		return false;
	}
}

bool PKB::isSecondEntity(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFollowee(statementTwo);
	case RelationRef::PARENT:
		return ParentStore::isChild(statementTwo);
	case RelationRef::FOLLOWS_T:
		return FollowsStore::isFolloweeT(statementTwo);
	case RelationRef::PARENT_T:
		return ParentStore::isChildT(statementTwo);
	default:
		return false;
	}
}

std::unordered_set<int> PKB::getFirstEntities(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getFollower(statementTwo);
	case RelationRef::PARENT:
		return ParentStore::getParent(statementTwo);
	case RelationRef::FOLLOWS_T:
		return FollowsStore::getFollowersT(statementTwo);
	case RelationRef::PARENT_T:
		return ParentStore::getParentsT(statementTwo);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getSecondEntities(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getFollowee(statementOne);
	case RelationRef::PARENT:
		return ParentStore::getChildren(statementOne);
	case RelationRef::FOLLOWS_T:
		return FollowsStore::getFolloweesT(statementOne);
	case RelationRef::PARENT_T:
		return ParentStore::getChildrenT(statementOne);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllFirstEntities(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFollowers();
	case RelationRef::PARENT:
		return ParentStore::getAllParents();
	case RelationRef::FOLLOWS_T:
		return FollowsStore::getAllFollowersT();
	case RelationRef::PARENT_T:
		return ParentStore::getAllParentsT();
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllSecondEntities(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFollowees();
	case RelationRef::PARENT:
		return ParentStore::getAllChildren();
	case RelationRef::FOLLOWS_T:
		return FollowsStore::getAllFolloweesT();
	case RelationRef::PARENT_T:
		return ParentStore::getAllChildrenT();
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllRelationshipPairs(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFollowsPairs();
	case RelationRef::PARENT:
		return ParentStore::getAllParentPairs();
	case RelationRef::FOLLOWS_T:
		return FollowsStore::getAllFollowsTPairs();
	case RelationRef::PARENT_T:
		return ParentStore::getAllParentTPairs();
	default:
		std::tuple<std::vector<int>, std::vector<int>> emptyResult;
		return emptyResult;
	}
}

/* Follows Getters */
bool PKB::hasFollowsRelationship() {
	return FollowsStore::hasFollowsRelationship();
}

bool PKB::hasFollowsTRelationship() {
	return FollowsStore::hasFollowsTRelationship();
}

bool PKB::isFollowsRelationship(int follower, int followee) {
	return FollowsStore::isFollowsRelationship(follower, followee);
}

bool PKB::isFollowsTRelationship(int follower, int followee) {
	return FollowsStore::isFollowsTRelationship(follower, followee);
}

bool PKB::isFollower(int follower) {
	return FollowsStore::isFollower(follower);
}

bool PKB::isFollowee(int followee) {
	return FollowsStore::isFollowee(followee);
}

bool PKB::isFollowerT(int follower) {
	return FollowsStore::isFollowerT(follower);
}

bool PKB::isFolloweeT(int followee) {
	return FollowsStore::isFolloweeT(followee);
}

std::unordered_set<int> PKB::getFollowee(int follower) {
	return FollowsStore::getFollowee(follower);
}

std::unordered_set<int> PKB::getFollower(int followee) {
	return FollowsStore::getFollower(followee);
}

std::unordered_set<int> PKB::getAllFollowees() {
	return FollowsStore::getAllFollowees();
}

std::unordered_set<int> PKB::getAllFollowers() {
	return FollowsStore::getAllFollowers();
}

std::unordered_set<int> PKB::getFolloweesT(int follower) {
	return FollowsStore::getFolloweesT(follower);
}

std::unordered_set<int> PKB::getFollowersT(int followee) {
	return FollowsStore::getFollowersT(followee);
}

std::unordered_set<int> PKB::getAllFolloweesT() {
	return FollowsStore::getAllFolloweesT();
}

std::unordered_set<int> PKB::getAllFollowersT() {
	return FollowsStore::getAllFollowersT();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllFollowsPairs() {
	return FollowsStore::getAllFollowsPairs();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllFollowsTPairs() {
	return FollowsStore::getAllFollowsTPairs();
}

/* Parent Getters */
bool PKB::hasParentRelationship() {
	return ParentStore::hasParentRelationship();
}

bool PKB::hasParentTRelationship() {
	return ParentStore::hasParentTRelationship();
}

bool PKB::isParentRelationship(int parent, int child) {
	return ParentStore::isParentRelationship(parent, child);
}

bool PKB::isParentTRelationship(int parent, int child) {
	return ParentStore::isParentTRelationship(parent, child);
}

bool PKB::isParent(int parent) {
	return ParentStore::isParent(parent);
}

bool PKB::isChild(int child) {
	return ParentStore::isChild(child);
}

bool PKB::isParentT(int parent) {
	return ParentStore::isParentT(parent);
}

bool PKB::isChildT(int child) {
	return ParentStore::isChildT(child);
}

std::unordered_set<int> PKB::getChildren(int parent) {
	return ParentStore::getChildren(parent);
}

std::unordered_set<int> PKB::getParent(int child) {
	return ParentStore::getParent(child);
}

std::unordered_set<int> PKB::getAllChildren() {
	return ParentStore::getAllChildren();
}

std::unordered_set<int> PKB::getAllParents() {
	return ParentStore::getAllParents();
}

std::unordered_set<int> PKB::getChildrenT(int parent) {
	return ParentStore::getChildrenT(parent);
}

std::unordered_set<int> PKB::getParentsT(int child) {
	return ParentStore::getParentsT(child);
}

std::unordered_set<int> PKB::getAllChildrenT() {
	return ParentStore::getAllChildrenT();
}

std::unordered_set<int> PKB::getAllParentsT() {
	return ParentStore::getAllParentsT();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentPairs() {
	return ParentStore::getAllParentPairs();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentTPairs() {
	return ParentStore::getAllParentTPairs();
}

/* Uses Getters */
std::unordered_set<int> PKB::getUsesStatements() {
	return usesStore.getStmtInRelationship();
}

std::unordered_set<std::string> PKB::getUsedVariables() {
	return usesStore.getVarInRelationship();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getStatementNumberToVariablesUsed() {
	return usesStore.getStmtToVarRelationship();
}

std::unordered_map<std::string, std::unordered_set<int>> PKB::getVariableToStatementNumbersUsedBy() {
	return usesStore.getVarToStmtRelationship();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getProcedureToVariablesUsed() {
	return usesStore.getProcToVarRelationship();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getVariableToProceduresUsedBy() {
	return usesStore.getVarToProcRelationship();
}

std::unordered_set<std::string> PKB::getVariablesUsedByStatement(int stmtNo) {
	return usesStore.getVarByStmt(stmtNo);
}
std::unordered_set<std::string> PKB::getVariablesUsedByProcedure(const std::string& procName) {
	return usesStore.getVarByProc(procName);
}
std::unordered_set<int> PKB::getStatementsUsingVariable(const std::string& variable) {
	return usesStore.getStmtByVar(variable);
}
std::unordered_set<std::string> PKB::getProcedureUsingVariable(const std::string& variable) {
	return usesStore.getProcByVar(variable);
}
std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getStmtsToUsedVariable(const std::unordered_set<int>& stmts) {
	return usesStore.getStmtToVarByStmts(stmts);
}

/* Modifies Getters */
std::unordered_set<int> PKB::getModifiesStatements() {
	return modifiesStore.getStmtInRelationship();
}

std::unordered_set<std::string> PKB::getModifiedVariables() {
	return modifiesStore.getVarInRelationship();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getStatementNumberToVariablesModified() {
	return modifiesStore.getStmtToVarRelationship();
}

std::unordered_map<std::string, std::unordered_set<int>> PKB::getVariableToStatementNumbersModifiedBy() {
	return modifiesStore.getVarToStmtRelationship();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getProcedureToVariablesModified() {
	return modifiesStore.getProcToVarRelationship();
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getVariableToProceduresModifiedBy() {
	return modifiesStore.getVarToProcRelationship();
}

std::unordered_set<std::string> PKB::getVariablesModifiedByStatement(int stmtNo) {
	return modifiesStore.getVarByStmt(stmtNo);
}

std::unordered_set<std::string> PKB::getVariablesModifiedByProcedure(const std::string& procName) {
	return modifiesStore.getVarByProc(procName);
}

std::unordered_set<int> PKB::getStatementsModifyingVariable(const std::string& variable) {
	return modifiesStore.getStmtByVar(variable);
}
std::unordered_set<std::string> PKB::getProcedureModifyingVariable(const std::string& variable) {
	return modifiesStore.getProcByVar(variable);
}
std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getStmtsToModifiedVariable(const std::unordered_set<int>& stmts) {
	return modifiesStore.getStmtToVarByStmts(stmts);
}
