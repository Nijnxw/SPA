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
	PKB::usesStore.clear();
	PKB::modifiesStore.clear();
	PKB::callsStore.clear();
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

bool PKB::addIfStatement(int statementNumber, std::unordered_set<std::string> conditionalVariables) {
	return entityStore.addIfStatement(statementNumber, conditionalVariables);
}

bool PKB::addWhileStatement(int statementNumber, std::unordered_set<std::string> conditionalVariables) {
	return entityStore.addWhileStatement(statementNumber, conditionalVariables);
}

bool PKB::addCallStatement(int statementNumber, std::string procedure) {
	return entityStore.addCallStatement(statementNumber, procedure);
}

bool PKB::addReadStatement(int statementNumber, std::string variable) {
	return entityStore.addReadStatement(statementNumber, variable);
}

bool PKB::addPrintStatement(int statementNumber, std::string variable) {
	return entityStore.addPrintStatement(statementNumber, variable);
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

bool PKB::addCalls(std::string caller, std::string callee) {
	return callsStore.addRelationship(caller, callee);
}

bool PKB::addCallsT(std::string caller, std::string callee) {
	return callsStore.addRelationshipT(caller, callee);
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

std::unordered_map<int, AssignStatement> PKB::getAssignStatementsToStructs() {
	return entityStore.getAssignStatementsToStructs();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getIfStatementsToConditionalVariables() {
	return entityStore.getIfStatementsToConditionalVariables();
}

std::unordered_map<int, std::unordered_set<std::string>> PKB::getWhileStatementsToConditionalVariables() {
	return entityStore.getWhileStatementsToConditionalVariables();
}

std::unordered_map<int, std::string> PKB::getCallStatementsToProcedures() {
	return entityStore.getCallStatementsToProcedures();
}

std::unordered_map<int, std::string> PKB::getPrintStatementsToVariables() {
	return entityStore.getPrintStatementsToVariables();
}

std::unordered_map<int, std::string> PKB::getReadStatementsToVariables() {
	return entityStore.getReadStatementsToVariables();
}

std::unordered_set<int> PKB::getStatementsWithType(EntityType statementType) {
	return entityStore.getStatementsWithType(statementType);
}

/* StmtStmt Getter Helpers */
bool PKB::hasStmtStmtRelationship(RelationRef relationship) {
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

bool PKB::isStmtStmtRelationship(RelationRef relationship, int statementOne, int statementTwo) {
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

bool PKB::isStmtStmtFirstEntity(RelationRef relationship, int statementOne) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.isFirstSynonym(statementOne);
		case RelationRef::PARENT:
			return parentStore.isFirstSynonym(statementOne);
		case RelationRef::FOLLOWS_T:
			return followsStore.isFirstSynonymT(statementOne);
		case RelationRef::PARENT_T:
			return parentStore.isFirstSynonymT(statementOne);
		default:
			return false;
	}
}

bool PKB::isStmtStmtSecondEntity(RelationRef relationship, int statementTwo) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.isSecondSynonym(statementTwo);
		case RelationRef::PARENT:
			return parentStore.isSecondSynonym(statementTwo);
		case RelationRef::FOLLOWS_T:
			return followsStore.isSecondSynonymT(statementTwo);
		case RelationRef::PARENT_T:
			return parentStore.isSecondSynonymT(statementTwo);
		default:
			return false;
	}
}

std::unordered_set<int> PKB::getStmtStmtFirstEntities(RelationRef relationship, int statementTwo) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.getFirstSynonyms(statementTwo);
		case RelationRef::PARENT:
			return parentStore.getFirstSynonyms(statementTwo);
		case RelationRef::FOLLOWS_T:
			return followsStore.getFirstSynonymsT(statementTwo);
		case RelationRef::PARENT_T:
			return parentStore.getFirstSynonymsT(statementTwo);
		default:
			std::unordered_set<int> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<int> PKB::getStmtStmtSecondEntities(RelationRef relationship, int statementOne) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.getSecondSynonyms(statementOne);
		case RelationRef::PARENT:
			return parentStore.getSecondSynonyms(statementOne);
		case RelationRef::FOLLOWS_T:
			return followsStore.getSecondSynonymsT(statementOne);
		case RelationRef::PARENT_T:
			return parentStore.getSecondSynonymsT(statementOne);
		default:
			std::unordered_set<int> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllStmtStmtFirstEntities(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.getAllFirstSynonyms();
		case RelationRef::PARENT:
			return parentStore.getAllFirstSynonyms();
		case RelationRef::FOLLOWS_T:
			return followsStore.getAllFirstSynonymsT();
		case RelationRef::PARENT_T:
			return parentStore.getAllFirstSynonymsT();
		default:
			std::unordered_set<int> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<int> PKB::getAllStmtStmtSecondEntities(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::FOLLOWS:
			return followsStore.getAllSecondSynonyms();
		case RelationRef::PARENT:
			return parentStore.getAllSecondSynonyms();
		case RelationRef::FOLLOWS_T:
			return followsStore.getAllSecondSynonymsT();
		case RelationRef::PARENT_T:
			return parentStore.getAllSecondSynonymsT();
		default:
			std::unordered_set<int> emptyResult;
			return emptyResult;
	}
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllStmtStmtRelationshipPairs(RelationRef relationship) {
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

/* ProcProc Getter Helpers */
bool PKB::hasProcProcRelationship(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.hasRelationship();
		case RelationRef::CALLS_T:
			return callsStore.hasTRelationship();
		default:
			return false;
	}
}

bool PKB::isProcProcRelationship(RelationRef relationship, std::string procOne, std::string procTwo) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.isRelationship(procOne, procTwo);
		case RelationRef::CALLS_T:
			return callsStore.isTRelationship(procOne, procTwo);
		default:
			return false;
	}
}

bool PKB::isProcProcFirstEntity(RelationRef relationship, std::string procOne) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.isFirstSynonym(procOne);
		case RelationRef::CALLS_T:
			return callsStore.isFirstSynonymT(procOne);
		default:
			return false;
	}
}

bool PKB::isProcProcSecondEntity(RelationRef relationship, std::string procTwo) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.isSecondSynonym(procTwo);
		case RelationRef::CALLS_T:
			return callsStore.isSecondSynonymT(procTwo);
		default:
			return false;
	}
}

std::unordered_set<std::string> PKB::getProcProcFirstEntities(RelationRef relationship, std::string procTwo) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.getFirstSynonyms(procTwo);
		case RelationRef::CALLS_T:
			return callsStore.getFirstSynonymsT(procTwo);
		default:
			std::unordered_set<std::string> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<std::string> PKB::getProcProcSecondEntities(RelationRef relationship, std::string procOne) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.getSecondSynonyms(procOne);
		case RelationRef::CALLS_T:
			return callsStore.getSecondSynonymsT(procOne);
		default:
			std::unordered_set<std::string> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<std::string> PKB::getAllProcProcFirstEntities(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.getAllFirstSynonyms();
		case RelationRef::CALLS_T:
			return callsStore.getAllFirstSynonymsT();
		default:
			std::unordered_set<std::string> emptyResult;
			return emptyResult;
	}
}

std::unordered_set<std::string> PKB::getAllProcProcSecondEntities(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.getAllSecondSynonyms();
		case RelationRef::CALLS_T:
			return callsStore.getAllSecondSynonymsT();
		default:
			std::unordered_set<std::string> emptyResult;
			return emptyResult;
	}
}

std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getAllProcProcRelationshipPairs(RelationRef relationship) {
	switch (relationship) {
		case RelationRef::CALLS:
			return callsStore.getAllRelationshipPairs();
		case RelationRef::CALLS_T:
			return callsStore.getAllRelationshipTPairs();
		default:
			std::tuple<std::vector<std::string>, std::vector<std::string>> emptyResult;
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
	return followsStore.isFirstSynonym(follower);
}

bool PKB::isFollowee(int followee) {
	return followsStore.isSecondSynonym(followee);
}

bool PKB::isFollowerT(int follower) {
	return followsStore.isFirstSynonymT(follower);
}

bool PKB::isFolloweeT(int followee) {
	return followsStore.isSecondSynonymT(followee);
}

std::unordered_set<int> PKB::getFollowee(int follower) {
	return followsStore.getSecondSynonyms(follower);
}

std::unordered_set<int> PKB::getFollower(int followee) {
	return followsStore.getFirstSynonyms(followee);
}

std::unordered_set<int> PKB::getAllFollowees() {
	return followsStore.getAllSecondSynonyms();
}

std::unordered_set<int> PKB::getAllFollowers() {
	return followsStore.getAllFirstSynonyms();
}

std::unordered_set<int> PKB::getFolloweesT(int follower) {
	return followsStore.getSecondSynonymsT(follower);
}

std::unordered_set<int> PKB::getFollowersT(int followee) {
	return followsStore.getFirstSynonymsT(followee);
}

std::unordered_set<int> PKB::getAllFolloweesT() {
	return followsStore.getAllSecondSynonymsT();
}

std::unordered_set<int> PKB::getAllFollowersT() {
	return followsStore.getAllFirstSynonymsT();
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
	return parentStore.isFirstSynonym(parent);
}

bool PKB::isChild(int child) {
	return parentStore.isSecondSynonym(child);
}

bool PKB::isParentT(int parent) {
	return parentStore.isFirstSynonymT(parent);
}

bool PKB::isChildT(int child) {
	return parentStore.isSecondSynonymT(child);
}

std::unordered_set<int> PKB::getChildren(int parent) {
	return parentStore.getSecondSynonyms(parent);
}

std::unordered_set<int> PKB::getParent(int child) {
	return parentStore.getFirstSynonyms(child);
}

std::unordered_set<int> PKB::getAllChildren() {
	return parentStore.getAllSecondSynonyms();
}

std::unordered_set<int> PKB::getAllParents() {
	return parentStore.getAllFirstSynonyms();
}

std::unordered_set<int> PKB::getChildrenT(int parent) {
	return parentStore.getSecondSynonymsT(parent);
}

std::unordered_set<int> PKB::getParentsT(int child) {
	return parentStore.getFirstSynonymsT(child);
}

std::unordered_set<int> PKB::getAllChildrenT() {
	return parentStore.getAllSecondSynonymsT();
}

std::unordered_set<int> PKB::getAllParentsT() {
	return parentStore.getAllFirstSynonymsT();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentPairs() {
	return parentStore.getAllRelationshipPairs();
}

std::tuple<std::vector<int>, std::vector<int>> PKB::getAllParentTPairs() {
	return parentStore.getAllRelationshipTPairs();
}

/* Calls Getters */
bool PKB::hasCallsRelationship() {
	return callsStore.hasRelationship();
}

bool PKB::hasCallsTRelationship() {
	return callsStore.hasTRelationship();
}

bool PKB::isCallsRelationship(std::string caller, std::string callee) {
	return callsStore.isRelationship(caller, callee);
}

bool PKB::isCallsTRelationship(std::string caller, std::string callee) {
	return callsStore.isTRelationship(caller, callee);
}

bool PKB::isCaller(std::string caller) {
	return callsStore.isFirstSynonym(caller);
}

bool PKB::isCallee(std::string callee) {
	return callsStore.isSecondSynonym(callee);
}

bool PKB::isCallerT(std::string caller) {
	return callsStore.isFirstSynonymT(caller);
}

bool PKB::isCalleeT(std::string callee) {
	return callsStore.isSecondSynonymT(callee);
}

std::unordered_set<std::string> PKB::getCallees(std::string caller) {
	return callsStore.getSecondSynonyms(caller);
}

std::unordered_set<std::string> PKB::getCaller(std::string callee) {
	return callsStore.getFirstSynonyms(callee);
}

std::unordered_set<std::string> PKB::getAllCallees() {
	return callsStore.getAllSecondSynonyms();
}

std::unordered_set<std::string> PKB::getAllCallers() {
	return callsStore.getAllFirstSynonyms();
}

std::unordered_set<std::string> PKB::getCalleesT(std::string caller) {
	return callsStore.getSecondSynonymsT(caller);
}

std::unordered_set<std::string> PKB::getCallersT(std::string callee) {
	return callsStore.getFirstSynonymsT(callee);
}

std::unordered_set<std::string> PKB::getAllCalleesT() {
	return callsStore.getAllSecondSynonymsT();
}

std::unordered_set<std::string> PKB::getAllCallersT() {
	return callsStore.getAllFirstSynonymsT();
}

std::tuple<std::vector<std::string>, std::vector<std::string>> PKB::getAllCallsPairs() {
	return callsStore.getAllRelationshipPairs();
}

std::tuple<std::vector<std::string>, std::vector<std::string>> PKB::getAllCallsTPairs() {
	return callsStore.getAllRelationshipTPairs();
}

/* Uses Getters */
std::unordered_set<int> PKB::getUsesStatements() {
	return usesStore.getStmtInRelationship();
}

std::unordered_set<std::string> PKB::getUsesProcedures() {
	return usesStore.getProcInRelationship();
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

// Helpers
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

std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getProcsToUsedVariable(const std::unordered_set<std::string>& procs) {
	return usesStore.getProcToVarByProcs(procs);
}

/* Modifies Getters */
std::unordered_set<int> PKB::getModifiesStatements() {
	return modifiesStore.getStmtInRelationship();
}

std::unordered_set<std::string> PKB::getModifiesProcedures() {
	return modifiesStore.getProcInRelationship();
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

// Helpers
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

std::tuple<std::vector<std::string>, std::vector<std::string>>
PKB::getProcsToModifiedVariable(const std::unordered_set<std::string>& procs) {
	return modifiesStore.getProcToVarByProcs(procs);
}
