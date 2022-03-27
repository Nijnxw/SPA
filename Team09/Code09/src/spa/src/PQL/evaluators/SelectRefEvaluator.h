#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "models/QueryClauseResult.h"
#include "models/QueryArgument.h"
#include "pkb/PKB.h"

class SelectRefEvaluator {
public:
	static void evaluate(Table& results,
						 const std::unordered_set<QueryArgument, std::hash<QueryArgument>>& args);
private:
	static void supplementResults(Table& results, const QueryArgument& arg);
};