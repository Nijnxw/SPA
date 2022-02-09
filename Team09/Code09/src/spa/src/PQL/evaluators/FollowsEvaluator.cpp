#include "FollowsEvaluator.h"

static QueryClauseTable
getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::FOLLOWS, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

static QueryClauseTable
getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getTransitiveRelationship(RelationRef::FOLLOWS, LHS, RHS, LHSType, RHSType, isBooleanResult);
}