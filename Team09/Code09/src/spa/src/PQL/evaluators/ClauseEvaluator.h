#pragma once

#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"
#include "WithEvaluator.h"
#include "NextEvaluator.h"
#include "CallsEvaluator.h"
#include "PatternWhileEvaluator.h"
#include "PatternIfEvaluator.h"
#include "PatternAssignEvaluator.h"
#include "ModifiesEvaluator.h"
#include "UsesEvaluator.h"
#include "ParentEvaluator.h"
#include "FollowsEvaluator.h"
#include "AffectsEvaluator.h"

class ClauseEvaluator {
public:
	ClauseEvaluator() = default;
	QueryClauseResult evaluate(const QueryClause& entity, bool isBooleanResult);
private:
	FollowsEvaluator followsEvaluator;
	ParentEvaluator parentEvaluator;
	UsesEvaluator usesEvaluator;
	ModifiesEvaluator modifiesEvaluator;
	PatternAssignEvaluator patternAssignEvaluator;
	PatternIfEvaluator patternIfEvaluator;
	PatternWhileEvaluator patternWhileEvaluator;
	CallsEvaluator callsEvaluator;
	NextEvaluator nextEvaluator;
	WithEvaluator withEvaluator;
	AffectsEvaluator affectsEvaluator;
};