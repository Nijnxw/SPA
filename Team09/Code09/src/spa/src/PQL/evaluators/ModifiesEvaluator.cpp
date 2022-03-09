#include "ModifiesEvaluator.h"

ModifiesEvaluator::ModifiesEvaluator()
	: StmtVarRelationshipEvaluator() {}

/* Get Modifies relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseResult
ModifiesEvaluator::getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return StmtVarRelationshipEvaluator::getRelationship(RelationRef::MODIFIES, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

