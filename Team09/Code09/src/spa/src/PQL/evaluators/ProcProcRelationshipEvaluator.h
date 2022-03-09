#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"

#include "RelationshipEvaluator.h"
#include "TransitiveRelationshipEvaluator.h"

class ProcProcRelationshipEvaluator : public RelationshipEvaluator, public TransitiveRelationshipEvaluator {
private:
	QueryClauseResult
		getRelationshipByProcedureString(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseResult
		getRelationshipByProcedureSynonym(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType);
	QueryClauseResult getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType);

public:
	QueryClauseResult getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);

	QueryClauseResult getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
};