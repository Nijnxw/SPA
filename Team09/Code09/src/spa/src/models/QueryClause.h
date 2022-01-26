#pragma once

#include <vector>
#include "QueryArgumentType.h"
#include "QueryArgument.h"

class QueryClause {
public:
    QueryClause(QueryArgumentType& clauseType, std::vector<QueryArgument>& arguments);

    QueryArgumentType GetClauseType() const;
    const std::vector<QueryArgument>& GetArguments() const;

protected:
    QueryArgumentType clauseType;
    std::vector<QueryArgument> arguments;
};
