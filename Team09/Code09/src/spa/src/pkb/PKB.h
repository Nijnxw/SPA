#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../models/AssignStatement.h"
#include "../models/EntityType.h"
#include "../models/QueryClauseTable.h"
#include "../models/QueryClause.h"
#include "../models/RelationRef.h"

#include "stores/EntityStore.h"
#include "stores/FollowsStore.h"
#include "stores/ParentStore.h"
#include "stores/UsesStore.h"
#include "stores/ModifiesStore.h"

class PKB {
public:
	PKB();

	static void clearAllStores();

	/* Setters called by SP and DE */
	static bool addProcedure(std::string procedure);
	static bool addVariable(std::string variable);
	static bool addConstant(std::string constant);
	static bool addStatementNumber(int statementNumber);

	static bool addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide);
	static bool addStatementWithType(EntityType statementType, int statementNumber);

	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);
	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);
	static bool addUsesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addUsesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);
	static bool addModifiesStatement(int statementNumber, const std::unordered_set<std::string>& variables);
	static bool addModifiesProcedure(const std::string& procedure, const std::unordered_set<std::string>& variables);

	/* Getters called by QE */
	static std::unordered_set<std::string> getProcedures();
	static std::unordered_set<std::string> getVariables();
	static std::unordered_set<std::string> getConstants();
	static std::unordered_set<int> getStatementNumbers();

	static std::unordered_map<int, AssignStatement> getAssignStatements();
	static std::unordered_set<int> getStatementsWithType(EntityType statementType);

	/* Follows and Parent Getters */
	static bool hasRelationship(RelationRef relationship);
	static bool isRelationship(RelationRef relationship, int statementOne, int statementTwo);
	static bool isFirstEntity(RelationRef relationship, int statementOne);
	static bool isSecondEntity(RelationRef relationship, int statementTwo);

	static std::unordered_set<int> getFirstEntities(RelationRef relationship, int statementTwo);
	static std::unordered_set<int> getSecondEntities(RelationRef relationship, int statementOne);

	static std::unordered_set<int> getAllFirstEntities(RelationRef relationship);
	static std::unordered_set<int> getAllSecondEntities(RelationRef relationship);

	static std::tuple<std::vector<int>, std::vector<int>> getAllRelationshipPairs(RelationRef relationship);

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

	/* Uses Getters */
	static std::unordered_set<int> getUsesStatements();
	static std::unordered_set<std::string> getUsedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersUsedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresUsedBy();
	static std::unordered_set<std::string> getVariablesUsedByStatement(int stmtNo);
	static std::unordered_set<std::string> getVariablesUsedByProcedure(const std::string& procName);
	static std::unordered_set<int> getStatementsUsingVariable(const std::string& variable);
	static std::tuple<std::vector<std::string>, std::vector<std::string>>
		getStmtsToUsedVariable(const std::unordered_set<int>& stmts);

	/* Modifies Getters */
	static std::unordered_set<int> getModifiesStatements();
	static std::unordered_set<std::string> getModifiedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersModifiedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresModifiedBy();
};
