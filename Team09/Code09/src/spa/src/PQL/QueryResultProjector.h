#pragma once

#include "models/QueryClauseTable.h"
#include "models/QueryArgument.h"
#include <list>

class QueryResultProjector {
public:
	static std::list<std::string> formatResult(Table& res, std::vector<QueryArgument>& selectSyn);
};
