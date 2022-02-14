#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"

#include "RelationshipEvaluator.h"
#include "TransitiveRelationshipEvaluator.h"

class StmtStmtRelationshipEvaluator : public RelationshipEvaluator, public TransitiveRelationshipEvaluator {
private:
	QueryClauseTable
		getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable
		getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType);

public:
	QueryClauseTable getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);

	QueryClauseTable getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
};