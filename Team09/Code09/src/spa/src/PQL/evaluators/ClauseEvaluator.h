#include "models/QueryClauseTable.h"
#include "models/QueryClause.h"

class ClauseEvaluator {
public:
	static QueryClauseTable evaluate(QueryClause& entity, bool isBooleanResult);
};