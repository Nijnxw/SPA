#pragma once

#include "QueryClause.h"

class QueryPatternClause : public QueryClause {
public:
    QueryPatternClause(QueryArgument& patternSynonym, std::vector<QueryArgument>& arguments, bool IsMatchExact);

    bool IsMatchExact() const;
    const QueryArgument& GetPatternSynonym() const;

private:
    QueryArgument patternSynonym;
    bool isMatchExact;  // isMatchExact is true if no wild card is provided in the pattern
};
