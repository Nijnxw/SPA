#pragma once

#include <vector>
#include <unordered_map>
#include "models/Query.h"
#include "models/QueryClauseTable.h"
#include "pkb/stores/ModifiesStore.h"
#include "pkb/stores/UsesStore.h"

class QueryEvaluator {
public:
	static Table evaluate(Query& query);
};
