#include "ClauseEvaluator.h"
#include "models/QueryClause.h"
#include "FollowsEvaluator.h"
#include "UsesEvaluator.h"
#include "ParentEvaluator.h"
#include "ModifiesEvaluator.h"

QueryClauseTable ClauseEvaluator::evaluate(QueryClause& clause, bool isBooleanResult) {
	QueryArgument firstArg = clause.getArguments().at(0);
	QueryArgument secondArg = clause.getArguments().at(1);

	FollowsEvaluator followsEvaluator = FollowsEvaluator();
	ParentEvaluator parentEvaluator = ParentEvaluator();

	switch (clause.getClauseType()) {
		case RelationRef::FOLLOWS:
			return followsEvaluator.getFollows(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
												secondArg.getType(), isBooleanResult);
		case RelationRef::FOLLOWS_T:
			return followsEvaluator.getFollowsT(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
												 secondArg.getType(), isBooleanResult);
		case RelationRef::MODIFIES:
			return ModifiesEvaluator::getModifies(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
												  secondArg.getType(), isBooleanResult);
		case RelationRef::PARENT:
			return parentEvaluator.getParent(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											  secondArg.getType(), isBooleanResult);
		case RelationRef::PARENT_T:
			return parentEvaluator.getParentT(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
											   secondArg.getType(), isBooleanResult);
		case RelationRef::USES:
			return UsesEvaluator::getUses(firstArg.getValue(), secondArg.getValue(), firstArg.getType(),
										  secondArg.getType(), isBooleanResult);
		default:
			return {};
	}
}
