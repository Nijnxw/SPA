#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

#include "StmtStmtRelationshipEvaluator.h"

class NextEvaluator : public StmtStmtRelationshipEvaluator {
private:
	QueryClauseResult getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
	
	QueryClauseResult getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
	
public:
	NextEvaluator();

	QueryClauseResult
	getNext(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			  bool isBooleanResult);
	
	QueryClauseResult
	getNextT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
