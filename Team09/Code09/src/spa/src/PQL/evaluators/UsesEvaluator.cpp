#include "UsesEvaluator.h"

UsesEvaluator::UsesEvaluator()
	: StmtVarRelationshipEvaluator() {}

/* Get Uses relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseResult
UsesEvaluator::getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return StmtVarRelationshipEvaluator::getRelationship(RelationRef::USES, LHS, RHS, LHSType, RHSType, isBooleanResult);
}
