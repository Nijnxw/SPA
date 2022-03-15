#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../models/AssignStatement.h"
#include "../models/EntityType.h"
#include "../models/QueryClauseResult.h"
#include "../models/QueryClause.h"
#include "../models/RelationRef.h"

#include "stores/EntityStore.h"
#include "stores/FollowsStore.h"
#include "stores/ParentStore.h"
#include "stores/CallsStore.h"
#include "stores/UsesStore.h"
#include "stores/ModifiesStore.h"
#include "stores/NextStore.h"

class PKB {
private:
	static inline EntityStore entityStore;
	static inline FollowsStore followsStore;
	static inline ParentStore parentStore;
	static inline CallsStore callsStore;
	static inline UsesStore usesStore;
	static inline ModifiesStore modifiesStore;
	static inline NextStore nextStore;
public:
	PKB();

	static void clearAllStores();

	/* Setters called by SP and DE */
	static bool addProcedure(std::string procedure);
	static bool addVariable(std::string variable);
	static bool addConstant(std::string constant);
	static bool addStatementNumber(int statementNumber);

	static bool addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide);
	static bool addIfStatement(int statementNumber, std::unordered_set<std::string> conditionalVariables);
	static bool addWhileStatement(int statementNumber, std::unordered_set<std::string> conditionalVariables);
	static bool addCallStatement(int statementNumber, std::string procedure);
	static bool addReadStatement(int statementNumber, std::string variable);
	static bool addPrintStatement(int statementNumber, std::string variable);

	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);
	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);
	static bool addCalls(std::string caller, std::string callee);
	static bool addCallsT(std::string caller, std::string callee);
	static bool addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);
	static bool addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);
	static bool addCFG(const std::vector<std::unordered_set<int>>& cfg);
	static bool addProcedureNameToLastCFGNode(const std::string procedure, const std::unordered_set<int> lastNodes);

	/* Getters called by QE */
	static std::unordered_set<std::string> getProcedures();
	static std::unordered_set<std::string> getVariables();
	static std::unordered_set<std::string> getConstants();
	static std::unordered_set<int> getStatementNumbers();

	static std::unordered_map<int, AssignStatement> getAssignStatementsToStructs();
	static std::unordered_map<int, std::unordered_set<std::string>> getIfStatementsToConditionalVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getWhileStatementsToConditionalVariables();
	static std::unordered_map<int, std::string> getCallStatementsToProcedures();
	static std::unordered_map<int, std::string> getPrintStatementsToVariables();
	static std::unordered_map<int, std::string> getReadStatementsToVariables();

	static std::unordered_set<int> getStatementsWithType(EntityType statementType);

	/* StmtStmt Getters */
	static bool hasStmtStmtRelationship(RelationRef relationship);
	static bool isStmtStmtRelationship(RelationRef relationship, int statementOne, int statementTwo);
	static bool isStmtStmtFirstEntity(RelationRef relationship, int statementOne);
	static bool isStmtStmtSecondEntity(RelationRef relationship, int statementTwo);

	static std::unordered_set<int> getStmtStmtFirstEntities(RelationRef relationship, int statementTwo);
	static std::unordered_set<int> getStmtStmtSecondEntities(RelationRef relationship, int statementOne);

	static std::unordered_set<int> getAllStmtStmtFirstEntities(RelationRef relationship);
	static std::unordered_set<int> getAllStmtStmtSecondEntities(RelationRef relationship);

	static std::tuple<std::vector<int>, std::vector<int>> getAllStmtStmtRelationshipPairs(RelationRef relationship);

	/* ProcProc Getters */
	static bool hasProcProcRelationship(RelationRef relationship);
	static bool isProcProcRelationship(RelationRef relationship, std::string procOne, std::string procTwo);
	static bool isProcProcFirstEntity(RelationRef relationship, std::string procOne);
	static bool isProcProcSecondEntity(RelationRef relationship, std::string procTwo);

	static std::unordered_set<std::string> getProcProcFirstEntities(RelationRef relationship, std::string procTwo);
	static std::unordered_set<std::string> getProcProcSecondEntities(RelationRef relationship, std::string procOne);

	static std::unordered_set<std::string> getAllProcProcFirstEntities(RelationRef relationship);
	static std::unordered_set<std::string> getAllProcProcSecondEntities(RelationRef relationship);

	static std::tuple<std::vector<std::string>, std::vector<std::string>> getAllProcProcRelationshipPairs(RelationRef relationship);

	/* Follows Getters */
	static bool hasFollowsRelationship();
	static bool hasFollowsTRelationship();

	static bool isFollowsRelationship(int follower, int followee);
	static bool isFollowsTRelationship(int follower, int followee);
	static bool isFollower(int follower);
	static bool isFollowee(int followee);
	static bool isFollowerT(int follower);
	static bool isFolloweeT(int followee);

	static std::unordered_set<int> getFollowee(int follower);
	static std::unordered_set<int> getFollower(int followee);
	static std::unordered_set<int> getAllFollowees();
	static std::unordered_set<int> getAllFollowers();

	static std::unordered_set<int> getFolloweesT(int follower);
	static std::unordered_set<int> getFollowersT(int followee);
	static std::unordered_set<int> getAllFolloweesT();
	static std::unordered_set<int> getAllFollowersT();

	static std::tuple<std::vector<int>, std::vector<int>> getAllFollowsPairs();
	static std::tuple<std::vector<int>, std::vector<int>> getAllFollowsTPairs();

	/* Parent Getters */
	static bool hasParentRelationship();
	static bool hasParentTRelationship();

	static bool isParentRelationship(int parent, int child);
	static bool isParentTRelationship(int parent, int child);
	static bool isParent(int parent);
	static bool isChild(int child);
	static bool isParentT(int parent);
	static bool isChildT(int child);

	static std::unordered_set<int> getChildren(int parent);
	static std::unordered_set<int> getParent(int child);
	static std::unordered_set<int> getAllChildren();
	static std::unordered_set<int> getAllParents();

	static std::unordered_set<int> getChildrenT(int parent);
	static std::unordered_set<int> getParentsT(int child);
	static std::unordered_set<int> getAllChildrenT();
	static std::unordered_set<int> getAllParentsT();

	static std::tuple<std::vector<int>, std::vector<int>> getAllParentPairs();
	static std::tuple<std::vector<int>, std::vector<int>> getAllParentTPairs();

	/* Next Getters */
	static bool hasNextRelationship();
	static bool isNextRelationship(int previousStatement, int nextStatement);

	static bool isPreviousStatement(int previousStatement);
	static bool isNextStatement(int nextStatement);

	static std::unordered_set<int> getNextStatements(int previousStatement);
	static std::unordered_set<int> getPreviousStatements(int nextStatement);

	static std::unordered_set<int> getAllNextStatements();
	static std::unordered_set<int> getAllPreviousStatements();

	static std::tuple<std::vector<int>, std::vector<int>> getAllNextPairs();

	static std::vector<std::unordered_set<int>> getCFG();
	static std::vector<std::unordered_set<int>> getReversedCFG();
	static std::unordered_map<std::string, std::unordered_set<int>> getProcedureNameToLastCFGNode();

	/* Calls Getters */
	static bool hasCallsRelationship();
	static bool hasCallsTRelationship();

	static bool isCallsRelationship(std::string caller, std::string callee);
	static bool isCallsTRelationship(std::string caller, std::string callee);
	static bool isCaller(std::string caller);
	static bool isCallee(std::string callee);
	static bool isCallerT(std::string caller);
	static bool isCalleeT(std::string callee);

	static std::unordered_set<std::string> getCallees(std::string caller);
	static std::unordered_set<std::string> getCaller(std::string callee);
	static std::unordered_set<std::string> getAllCallees();
	static std::unordered_set<std::string> getAllCallers();

	static std::unordered_set<std::string> getCalleesT(std::string caller);
	static std::unordered_set<std::string> getCallersT(std::string callee);
	static std::unordered_set<std::string> getAllCalleesT();
	static std::unordered_set<std::string> getAllCallersT();

	static std::tuple<std::vector<std::string>, std::vector<std::string>> getAllCallsPairs();
	static std::tuple<std::vector<std::string>, std::vector<std::string>> getAllCallsTPairs();

	/* Uses Getters */
	static std::unordered_set<int> getUsesStatements();
	static std::unordered_set<std::string> getUsesProcedures();
	static std::unordered_set<std::string> getUsedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersUsedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresUsedBy();
	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsUsingVariable(const std::string& variable);
	static std::unordered_set<std::string> getProcedureUsingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getStmtsToUsedVariable(const std::unordered_set<int>& stmts);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getProcsToUsedVariable(const std::unordered_set<std::string>& procs);

	/* Modifies Getters */
	static std::unordered_set<int> getModifiesStatements();
	static std::unordered_set<std::string> getModifiesProcedures();
	static std::unordered_set<std::string> getModifiedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersModifiedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresModifiedBy();
	static std::unordered_set<std::string> getVariablesModifiedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesModifiedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsModifyingVariable(const std::string& variable);
	static std::unordered_set<std::string> getProcedureModifyingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getStmtsToModifiedVariable(const std::unordered_set<int>& stmts);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getProcsToModifiedVariable(const std::unordered_set<std::string>& procs);
};