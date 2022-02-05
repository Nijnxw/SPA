#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../models/AssignStatement.h"
#include "../models/entityType.h"
#include "../models/QueryClauseTable.h"
#include "../models/QueryClause.h"

#include "stores/EntityStore.h"
#include "stores/FollowsStore.h"
#include "stores/ParentStore.h"
#include "stores/UsesStore.h"
#include "stores/ModifiesStore.h"
#include "evaluators/UsesEvaluator.h"

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


	static QueryClauseTable getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	static QueryClauseTable getUses(const QueryClause& queryClause, bool isBooleanResult);
	static QueryClauseTable getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
};