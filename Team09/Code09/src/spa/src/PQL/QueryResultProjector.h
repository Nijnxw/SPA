#pragma once

#include "models/QueryClauseTable.h"
#include "models/QueryArgument.h"

class QueryResultProjector {
public:
	static std::unordered_set<std::string> formatResult(Table& res, std::vector<QueryArgument>& selectSyn);
};
