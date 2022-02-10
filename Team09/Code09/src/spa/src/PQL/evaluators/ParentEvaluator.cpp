#include "ParentEvaluator.h"

QueryClauseTable
ParentEvaluator::getParent(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::PARENT, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseTable
ParentEvaluator::getParentT(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType,
	bool isBooleanResult) {
	return StatementOnlyRelationshipEvaluator::getRelationship(RelationRef::PARENT_T, LHS, RHS, LHSType, RHSType, isBooleanResult);
}