#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

#include "ProcProcRelationshipEvaluator.h"

class CallsEvaluator : public ProcProcRelationshipEvaluator {
private:
	QueryClauseResult getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
	QueryClauseResult getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
public:
	CallsEvaluator();

	QueryClauseResult
		getCalls(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
	QueryClauseResult
		getCallsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
			bool isBooleanResult);
};
