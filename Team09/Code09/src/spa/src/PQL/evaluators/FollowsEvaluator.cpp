#include "FollowsEvaluator.h"

FollowsEvaluator::FollowsEvaluator()
	: StmtStmtRelationshipEvaluator() {}

QueryClauseResult FollowsEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult FollowsEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getTransitiveRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
FollowsEvaluator::getFollows(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return FollowsEvaluator::getRelationship(RelationRef::FOLLOWS, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
FollowsEvaluator::getFollowsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return FollowsEvaluator::getTransitiveRelationship(RelationRef::FOLLOWS_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}