#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"
#include "models/QueryClauseTable.h"
#include "models/QueryClause.h"
#include "models/RelationRef.h"

#include "RelationshipEvaluator.h"

class UMEvaluator : public RelationshipEvaluator {
public:
	QueryClauseTable
		getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);

private:
	QueryClauseTable getRelationshipByUnderscore(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
	QueryClauseTable getRelationshipByVariable(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
	QueryClauseTable getRelationshipBySynonym(
		RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType);
};
