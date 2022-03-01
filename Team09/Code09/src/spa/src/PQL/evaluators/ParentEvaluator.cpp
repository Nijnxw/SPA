#include "ParentEvaluator.h"

ParentEvaluator::ParentEvaluator()
	: StmtStmtRelationshipEvaluator() {}

QueryClauseResult ParentEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult ParentEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getTransitiveRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
ParentEvaluator::getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ParentEvaluator::getRelationship(RelationRef::PARENT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
ParentEvaluator::getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ParentEvaluator::getTransitiveRelationship(RelationRef::PARENT_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}