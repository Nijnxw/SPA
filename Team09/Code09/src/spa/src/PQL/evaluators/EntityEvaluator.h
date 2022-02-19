#pragma once

#include "models/QueryClauseResult.h"
#include "models/QueryArgument.h"

class EntityEvaluator {
public:
	static QueryClauseResult evaluate(QueryArgument& entity);

private:
	template<typename T>
	static std::vector<std::string> keySetIntToStringVector(const std::unordered_map<int, T>& map);
	static std::vector<std::string> setIntToStringVector(const std::unordered_set<int>& set);
};
