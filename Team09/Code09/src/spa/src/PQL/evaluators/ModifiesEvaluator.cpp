#include "ModifiesEvaluator.h"

/* Get Modifies relationship information from PKB, note that LHS and RHS types have to be specified */
QueryClauseTable
ModifiesEvaluator::getModifies(const std::string& LHS, const std::string& RHS, EntityType LHSType, EntityType RHSType, bool isBooleanResult) {
	return UMEvaluator::getRelationship(RelationRef::MODIFIES, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

