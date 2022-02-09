#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "pkb/PKB.h"
#include "pkb/util/PKBUtil.cpp"
#include "models/EntityType.h"

#include "RelationshipEvaluatorInterface.h"
#include "TransitiveRelationshipEvaluatorInterface.h"

class StatementOnlyRelationshipEvaluator : public RelationshipEvaluatorInterface, public TransitiveRelationshipEvaluatorInterface {
private:
	RelationRef relationship;
	QueryClauseTable
		getRelationshipByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable
		getRelationshipByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType);

	QueryClauseTable
		getRelationshipTByStatementNumber(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable
		getRelationshipTByStatementVariable(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType RHSType);
	QueryClauseTable getRelationshipTByUnderscore(RelationRef relationship, const std::string& RHS, EntityType RHSType);
public:
	static QueryClauseTable getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
	static QueryClauseTable getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
		bool isBooleanResult);
};