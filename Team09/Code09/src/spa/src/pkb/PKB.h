#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "models/AssignStatement.h"
#include "models/EntityType.h"
#include "stores/EntityStore.h"
#include "stores/FollowsStore.h"
#include "stores/ParentStore.h"
#include "stores/UsesStore.h"
#include "stores/ModifiesStore.h"

class PKB {
public:
	PKB();

	static void clearAllStores();

	/* Getters called by Source Processor */
	static bool addProcedure(std::string procedure);
	static bool addVariable(std::string variable);
	static bool addConstant(std::string constant);
	static bool addStatementNumber(int statementNumber);

	static bool addAssignStatement(int statementNumber, std::string leftHandSide, std::string rightHandSide);
	static bool addStatement(EntityType statementType, int statementNumber);

	static bool addFollows(int follower, int followee);
	static bool addFollowsT(int follower, int followee);
	static bool addParent(int parent, int child);
	static bool addParentT(int parent, int child);
	static bool addUsesStatement(int statementNumber, EntityType statementType, std::unordered_set<std::string> variables);
	static bool addUsesProcedure(std::string procedure, EntityType statementType, std::unordered_set<std::string> variables);
	static bool addModifiesStatement(int statementNumber, EntityType statementType, std::unordered_set<std::string> variables);
	static bool addModifiesProcedure(std::string procedure, EntityType statementType, std::unordered_set<std::string> variables);

	/* Setters called by Query Evaluator */
	static std::unordered_set<std::string> getAllProcedures();
	static std::unordered_set<std::string> getAllVariables();
	static std::unordered_set<std::string> getAllConstants();
	static std::unordered_set<int> getAllStatements();

	static std::unordered_set<int> getAllAssignStatements();
	static std::unordered_set<int> getAllStatements(EntityType statementType);
};