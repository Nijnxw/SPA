#include "CallsEvaluator.h"

CallsEvaluator::CallsEvaluator()
	: ProcProcRelationshipEvaluator() {}

QueryClauseResult CallsEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ProcProcRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult CallsEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return ProcProcRelationshipEvaluator::getTransitiveRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
CallsEvaluator::getCalls(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return CallsEvaluator::getRelationship(RelationRef::CALLS, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
CallsEvaluator::getCallsT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return CallsEvaluator::getTransitiveRelationship(RelationRef::CALLS_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}