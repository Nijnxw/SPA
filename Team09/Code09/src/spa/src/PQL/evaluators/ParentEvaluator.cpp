#include "ParentEvaluator.h"

ParentEvaluator::ParentEvaluator()
	: StmtStmtRelationshipEvaluator() {}

QueryClauseTable ParentEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable ParentEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getTransitiveRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable
ParentEvaluator::getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ParentEvaluator::getRelationship(RelationRef::PARENT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable
ParentEvaluator::getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ParentEvaluator::getTransitiveRelationship(RelationRef::PARENT_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}