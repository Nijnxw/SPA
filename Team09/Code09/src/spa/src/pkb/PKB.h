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
	static bool hasTransitiveRelationship(RelationRef relationship);
	static bool isRelationship(RelationRef relationship, int statementOne, int statementTwo);
	static bool isTransitiveRelationship(RelationRef relationship, int statementOne, int statementTwo);
	static bool isFirstEntity(RelationRef relationship, int statementOne);
	static bool isSecondEntity(RelationRef relationship, int statementTwo);
	static bool isFirstEntityTransitive(RelationRef relationship, int statementOne);
	static bool isSecondEntityTransitive(RelationRef relationship, int statementTwo);

	static std::unordered_set<int> PKB::getFirstEntities(RelationRef relationship, int statementTwo);
	static std::unordered_set<int> PKB::getSecondEntities(RelationRef relationship, int statementOne);
	static std::unordered_set<int> PKB::getFirstEntitiesTransitive(RelationRef relationship, int statementTwo);
	static std::unordered_set<int> PKB::getSecondEntitiesTransitive(RelationRef relationship, int statementOne);

	static std::unordered_set<int> PKB::getAllFirstEntities(RelationRef relationship);
	static std::unordered_set<int> PKB::getAllSecondEntities(RelationRef relationship);
	static std::unordered_set<int> PKB::getAllFirstEntitiesTransitive(RelationRef relationship);
	static std::unordered_set<int> PKB::getAllSecondEntitiesTransitive(RelationRef relationship);

	static std::tuple<std::vector<int>, std::vector<int>> PKB::getAllRelationshipPairs(RelationRef relationship);
	static std::tuple<std::vector<int>, std::vector<int>> PKB::getAllRelationshipTransitivePairs(RelationRef relationship);

	/* Uses Getters */
	static std::unordered_set<int> getUsesStatements();
	static std::unordered_set<std::string> getUsedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersUsedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesUsed();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresUsedBy();

	/* Modifies Getters */
	static std::unordered_set<int> getModifiesStatements();
	static std::unordered_set<std::string> getModifiedVariables();
	static std::unordered_map<int, std::unordered_set<std::string>> getStatementNumberToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<int>> getVariableToStatementNumbersModifiedBy();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getProcedureToVariablesModified();
	static std::unordered_map<std::string, std::unordered_set<std::string>> getVariableToProceduresModifiedBy();
};
