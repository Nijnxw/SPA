#include "ParentEvaluator.h"

static QueryClauseTable
getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::PARENT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

static QueryClauseTable
getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getTransitiveRelationship(RelationRef::PARENT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}