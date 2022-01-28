#pragma once

#include <vector>
#include "QueryArgumentType.h"
#include "QueryArgument.h"

class QueryClause {
public:
    QueryClause(std::vector<QueryArgument>& arguments);

    const std::vector<QueryArgument>& GetArguments() const;

protected:
    std::vector<QueryArgument> arguments;
};
