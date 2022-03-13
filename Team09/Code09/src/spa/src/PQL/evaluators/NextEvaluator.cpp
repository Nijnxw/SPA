#include "NextEvaluator.h"

NextEvaluator::NextEvaluator()
	: StmtStmtRelationshipEvaluator() {}

QueryClauseResult NextEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult NextEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StmtStmtRelationshipEvaluator::getTransitiveRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
NextEvaluator::getNext(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return NextEvaluator::getRelationship(RelationRef::NEXT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
NextEvaluator::getNextT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return NextEvaluator::getTransitiveRelationship(RelationRef::NEXT_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

