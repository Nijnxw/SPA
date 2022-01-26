#pragma once

#include "QueryClause.h"

class QueryPatternClause : public QueryClause {
public:
    QueryPatternClause(QueryArgumentType& clauseType, std::vector<QueryArgument>& arguments,
                       QueryArgument& patternSynonym,
                       bool isMatchExact);

    bool IsMatchExact() const;
    const QueryArgument& GetPatternSynonym() const;

private:
    QueryArgument patternSynonym;
    bool isMatchExact;  // isMatchExact is true if no wild card is provided in the pattern
};
