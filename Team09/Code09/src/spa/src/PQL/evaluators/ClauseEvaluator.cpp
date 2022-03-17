#include "ClauseEvaluator.h"
#include "models/QueryClause.h"
#include "FollowsEvaluator.h"
#include "UsesEvaluator.h"
#include "ParentEvaluator.h"
#include "ModifiesEvaluator.h"
#include "PatternAssignEvaluator.h"
#include "PatternIfEvaluator.h"
#include "PatternWhileEvaluator.h"
#include "CallsEvaluator.h"
#include "WithEvaluator.h"

QueryClauseResult ClauseEvaluator::evaluate(const QueryClause& clause, bool isBooleanResult) {
	QueryArgument firstArg = clause.getArguments().at(0);
	QueryArgument secondArg = clause.getArguments().at(1);

	FollowsEvaluator followsEvaluator = FollowsEvaluator();
	ParentEvaluator parentEvaluator = ParentEvaluator();
	UsesEvaluator usesEvaluator = UsesEvaluator();
	ModifiesEvaluator modifiesEvaluator = ModifiesEvaluator();
	PatternAssignEvaluator patternAssignEvaluator = PatternAssignEvaluator();
	PatternIfEvaluator patternIfEvaluator = PatternIfEvaluator();
	PatternWhileEvaluator patternWhileEvaluator = PatternWhileEvaluator();
	CallsEvaluator callsEvaluator = CallsEvaluator();
	WithEvaluator withEvaluator = WithEvaluator();

	switch (clause.getClauseType()) {
		case RelationRef::FOLLOWS:
			return followsEvaluator.getFollows(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											   secondArg.getType(), isBooleanResult);
		case RelationRef::FOLLOWS_T:
			return followsEvaluator.getFollowsT(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
												secondArg.getType(), isBooleanResult);
		case RelationRef::MODIFIES:
			return modifiesEvaluator.getModifies(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
												 secondArg.getType(), isBooleanResult);
		case RelationRef::PARENT:
			return parentEvaluator.getParent(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											 secondArg.getType(), isBooleanResult);
		case RelationRef::PARENT_T:
			return parentEvaluator.getParentT(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											  secondArg.getType(), isBooleanResult);
		case RelationRef::USES:
			return usesEvaluator.getUses(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
										 secondArg.getType(), isBooleanResult);
		case RelationRef::PATTERN_ASSIGN:
			return patternAssignEvaluator.getPattern(firstArg.getValue(), secondArg.getValue(),
													 clause.getClauseSynonym(), firstArg.getType(),
													 secondArg.getType(), isBooleanResult);
		case RelationRef::PATTERN_IF:
			return patternIfEvaluator.getIfPattern(firstArg.getValue(), clause.getClauseSynonym(), firstArg.getType(), isBooleanResult);
		case RelationRef::PATTERN_WHILE:
			return patternWhileEvaluator.getWhilePattern(firstArg.getValue(), clause.getClauseSynonym(), firstArg.getType(), isBooleanResult);
		case RelationRef::CALLS:
			return callsEvaluator.getCalls(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
										   secondArg.getType(), isBooleanResult);
		case RelationRef::CALLS_T:
			return callsEvaluator.getCallsT(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											secondArg.getType(), isBooleanResult);
		case RelationRef::WITH:
			return withEvaluator.getWith(firstArg.getValue(), firstArg.getType(), firstArg.getAttrRef(),
				secondArg.getValue(), secondArg.getType(), secondArg.getAttrRef(), isBooleanResult);
		default:
			return {};
	}
}
