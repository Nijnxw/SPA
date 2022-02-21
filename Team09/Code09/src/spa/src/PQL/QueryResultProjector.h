#pragma once

#include "models/QueryClauseResult.h"
#include "models/QueryArgument.h"
#include <unordered_set>

class QueryResultProjector {
public:
	static std::unordered_set<std::string> formatResult(Table& res, std::vector<QueryArgument>& selectSyn);
};
