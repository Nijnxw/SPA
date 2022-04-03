#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"
#include "models/RelationRef.h"

#include "RelationshipEvaluator.h"

class StmtVarRelationshipEvaluator : public RelationshipEvaluator {
public:
	QueryClauseResult
		getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);

private:
	QueryClauseResult getRelationshipByUnderscore(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, bool isBooleanResult);
	QueryClauseResult getRelationshipByVariable(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, bool isBooleanResult);
	QueryClauseResult getRelationshipBySynonym(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, bool isBooleanResult);
};
