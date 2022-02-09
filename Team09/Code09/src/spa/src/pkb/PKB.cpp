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

/* Follows and Parent Getters */
bool PKB::hasRelationship(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::hasFollowsRelationship();
	case RelationRef::PARENT:
		return ParentStore::hasParentRelationship();
	default:
		return false;
	}
}

bool PKB::hasTransitiveRelationship(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::hasFollowsTRelationship();
	case RelationRef::PARENT:
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
	default:
		return false;
	}
}

bool PKB::isTransitiveRelationship(RelationRef relationship, int statementOne, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFollowsTRelationship(statementOne, statementTwo);
	case RelationRef::PARENT:
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
	default:
		return false;
	}
}

bool PKB::isFirstEntityTransitive(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFollowerT(statementOne);
	case RelationRef::PARENT:
		return ParentStore::isParentT(statementOne);
	default:
		return false;
	}
}

bool PKB::isSecondEntityTransitive(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::isFolloweeT(statementTwo);
	case RelationRef::PARENT:
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
		return ParentStore::getChildren(statementTwo);
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
		return ParentStore::getParent(statementOne);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getFirstEntitiesTransitive(RelationRef relationship, int statementTwo) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getFollowersT(statementTwo);
	case RelationRef::PARENT:
		return ParentStore::getChildrenT(statementTwo);
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getSecondEntitiesTransitive(RelationRef relationship, int statementOne) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getFolloweesT(statementOne);
	case RelationRef::PARENT:
		return ParentStore::getParentsT(statementOne);
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
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllFirstEntitiesTransitive(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFollowersT();
	case RelationRef::PARENT:
		return ParentStore::getAllParentsT();
	default:
		std::unordered_set<int> emptyResult;
		return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllSecondEntitiesTransitive(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFolloweesT();
	case RelationRef::PARENT:
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
	default:
		std::tuple<std::vector<int>, std::vector<int>> emptyResult;
		return emptyResult;
	}
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllRelationshipTransitivePairs(RelationRef relationship) {
	switch (relationship) {
	case RelationRef::FOLLOWS:
		return FollowsStore::getAllFollowsTPairs();
	case RelationRef::PARENT:
		return ParentStore::getAllParentTPairs();
	default:
		std::tuple<std::vector<int>, std::vector<int>> emptyResult;
		return emptyResult;
	}
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
