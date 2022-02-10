#include "FollowsEvaluator.h"

QueryClauseTable
FollowsEvaluator::getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::FOLLOWS, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable
FollowsEvaluator::getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::FOLLOWS_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}