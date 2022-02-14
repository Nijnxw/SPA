#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseTable.h"
#include "models/QueryClause.h"

#include "StmtStmtRelationshipEvaluator.h"

class FollowsEvaluator : public StmtStmtRelationshipEvaluator {
private: 
	QueryClauseTable getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
	QueryClauseTable getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
public:
	FollowsEvaluator();

	QueryClauseTable
		getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
	QueryClauseTable
		getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
