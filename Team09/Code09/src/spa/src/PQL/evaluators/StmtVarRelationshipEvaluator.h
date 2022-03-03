#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
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
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
	QueryClauseResult getRelationshipByVariable(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
	QueryClauseResult getRelationshipBySynonym(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
};