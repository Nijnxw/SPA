#include "ProcProcRelationshipEvaluator.h"

QueryClauseResult
ProcProcRelationshipEvaluator::getRelationship(RelationRef relationship, const std::string& LHS, const std::string& RHS,
											   EntityType LHSType, EntityType RHSType,
											   bool isBooleanResult) {
	QueryClauseResult emptyQueryResult;

	bool isValidCallsType = (LHSType == EntityType::PROC || LHSType == EntityType::STRING)
							&& (RHSType == EntityType::PROC || RHSType == EntityType::STRING);

	if (isValidCallsType && LHSType == RHSType && LHS == RHS) { // Edge case of same procedure calling same procedure
		return emptyQueryResult;
	} else if (LHSType == EntityType::STRING) {
		return ProcProcRelationshipEvaluator::getRelationshipByProcedureString(relationship, LHS, RHS, RHSType);
	} else if (LHSType == EntityType::PROC) {
		return ProcProcRelationshipEvaluator::getRelationshipByProcedureSynonym(relationship, LHS, RHS, LHSType,
																				RHSType);
	} else if (LHSType == EntityType::WILD) {
		return ProcProcRelationshipEvaluator::getRelationshipByUnderscore(relationship, RHS, RHSType);
	} else {
		return emptyQueryResult;
	}
}

QueryClauseResult
ProcProcRelationshipEvaluator::getTransitiveRelationship(RelationRef relationship, const std::string& LHS,
														 const std::string& RHS, EntityType LHSType, EntityType RHSType,
														 bool isBooleanResult) {
	return ProcProcRelationshipEvaluator::getRelationship(relationship, LHS, RHS, LHSType, RHSType, isBooleanResult);
}

QueryClauseResult
ProcProcRelationshipEvaluator::getRelationshipByProcedureString(RelationRef relationship, const std::string& LHS,
																const std::string& RHS, EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::STRING) { // Calls("First", "Second")
		if (PKB::isProcProcRelationship(relationship, LHS, RHS)) {
			queryResult.setBooleanResult(true);
		}
	} else if (RHSType == EntityType::PROC) { // Calls("First", p)
		if (PKB::isProcProcFirstEntity(relationship, LHS)) {
			const std::unordered_set<std::string>& procedures = PKB::getProcProcSecondEntities(relationship, LHS);
			queryResult.addColumn(RHS, procedures);
		}
	} else if (RHSType == EntityType::WILD) { // Calls("First", _)
		if (PKB::isProcProcFirstEntity(relationship, LHS)) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}


QueryClauseResult
ProcProcRelationshipEvaluator::getRelationshipByProcedureSynonym(RelationRef relationship, const std::string& LHS,
																 const std::string& RHS, EntityType LHSType,
																 EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::STRING) { // Calls(p, "Second")
		if (PKB::isProcProcSecondEntity(relationship, RHS)) {
			const std::unordered_set<std::string>& procedures = PKB::getProcProcFirstEntities(relationship, RHS);
			queryResult.addColumn(LHS, procedures);
		}
	} else if (RHSType == EntityType::PROC) { // Calls(p1, p2)
		const auto&[firstEntities, secondEntities] = PKB::getAllProcProcRelationshipPairs(relationship);
		queryResult.addColumn(LHS, firstEntities);
		queryResult.addColumn(RHS, secondEntities);
	} else if (RHSType == EntityType::WILD) { // Calls(p, _)
		const std::unordered_set<std::string>& procedures = PKB::getAllProcProcFirstEntities(relationship);
		queryResult.addColumn(LHS, procedures);
	}

	return queryResult;
}

QueryClauseResult
ProcProcRelationshipEvaluator::getRelationshipByUnderscore(RelationRef relationship, const std::string& RHS,
														   EntityType RHSType) {
	QueryClauseResult queryResult;

	if (RHSType == EntityType::STRING) { // Calls(_, "Second")
		if (PKB::isProcProcSecondEntity(relationship, RHS)) {
			queryResult.setBooleanResult(true);
		}
	} else if (RHSType == EntityType::PROC) { // Calls(_, p)
		const std::unordered_set<std::string>& procedures = PKB::getAllProcProcSecondEntities(relationship);
		queryResult.addColumn(RHS, procedures);
	} else if (RHSType == EntityType::WILD) { // Calls(_, _)
		if (PKB::hasProcProcRelationship(relationship)) {
			queryResult.setBooleanResult(true);
		}
	}

	return queryResult;
}