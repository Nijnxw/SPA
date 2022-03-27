#pragma once

#include <algorithm>
#include <iterator>
#include <tuple>
#include "models/QueryClause.h"
#include "models/Query.h"
#include "models/optimizer/OptimizerGroup.h"
#include "models/optimizer/OptimizerQuery.h"
#include "util/CommonUtils.cpp"

class Optimizer {
public:
	static std::tuple<std::unordered_set<QueryArgument, std::hash<QueryArgument>>, std::unordered_set<QueryArgument, std::hash<QueryArgument>>, std::vector<QueryClause>, std::vector<OptimizerGroup>>
	optimize(Query& query);
};
