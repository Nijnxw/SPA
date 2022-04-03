#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "util/PKBUtils.cpp"
#include "models/EntityType.h"

#include "RelationshipEvaluator.h"
#include "TransitiveRelationshipEvaluator.h"

class StmtStmtRelationshipEvaluator : public RelationshipEvaluator, public TransitiveRelationshipEvaluator {
protected:
	QueryClauseResult
		getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType, bool isBooleanResult);
	QueryClauseResult
		getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult);
	QueryClauseResult getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType, bool isBooleanResult);

	std::unordered_set<int> filterStatementsByType(std::unordered_set<int> statements, EntityType type, bool isBooleanResult);
	std::tuple<std::vector<int>, std::vector<int>> filterStatementPairsByType(const std::vector<int>& firstEntities,
		const std::vector<int>& secondEntities, EntityType LHSType, EntityType RHSType, bool isBooleanResult);

public:
	QueryClauseResult
	getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType,
					EntityType RHSType,
					bool isBooleanResult);

	QueryClauseResult
	getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS,
							  EntityType LHSType, EntityType RHSType,
							  bool isBooleanResult);
};