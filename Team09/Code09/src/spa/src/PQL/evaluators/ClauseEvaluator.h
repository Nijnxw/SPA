#include "models/QueryClauseResult.h"
#include "models/QueryClause.h"

class ClauseEvaluator {
public:
	static QueryClauseResult evaluate(QueryClause& entity, bool isBooleanResult);
};