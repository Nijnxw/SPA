#pragma once

#include <vector>
#include "EntityType.h"
#include "QueryArgument.h"

class QueryClause {
public:
    QueryClause(std::vector<QueryArgument>& arguments);

    const std::vector<QueryArgument>& getArguments() const;

protected:
    std::vector<QueryArgument> arguments;
};
