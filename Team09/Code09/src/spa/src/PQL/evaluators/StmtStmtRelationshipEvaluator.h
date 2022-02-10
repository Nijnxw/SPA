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
	static QueryClauseTable
		getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable
		getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	static QueryClauseTable getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType);

public:
	static QueryClauseTable getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
};