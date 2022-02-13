#include "UsesEvaluator.h"

/* Get Uses relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseTable
UsesEvaluator::getUses(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return UMEvaluator::getRelationship(RelationRef::USES, LHS, RHS, LHSType, RHSType, isBooleanResult);
}
