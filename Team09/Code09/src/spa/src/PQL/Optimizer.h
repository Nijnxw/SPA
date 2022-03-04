#pragma once

#include <algorithm>
#include <tuple>
#include "models/QueryClause.h"
#include "models/Query.h"
#include "models/optimizer/OptimizerGroup.h"
#include "models/optimizer/OptimizerQuery.h"
#include "util/CommonUtils.cpp"

class Optimizer {
public:
	static std::tuple<std::vector<QueryArgument>, std::vector<QueryClause>, std::vector<OptimizerGroup>, std::vector<OptimizerGroup>>
	optimize(Query& query);
private:
	static void
	splitGroups(std::vector<QueryArgument>& synNotInClauses, std::vector<OptimizerGroup>& groupsWithSelect,
				std::vector<OptimizerGroup>& groupsWithoutSelect, std::vector<OptimizerGroup>& allGroups, Query& query);
};
