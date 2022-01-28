#pragma once

#include <vector>
#include <unordered_map>
#include "models/Query.h"

class QueryEvaluator {
public:
    static std::unordered_map<std::string, std::vector<std::string>> evaluate(Query& query);

};
