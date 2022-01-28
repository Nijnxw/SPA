#pragma once

#include "QueryClause.h"

class QueryPatternClause : public QueryClause {
public:
    QueryPatternClause(QueryArgument& patternSynonym, std::vector<QueryArgument>& arguments, bool IsMatchExact);

    bool isMatchExact() const; // isMatchExact is true if no wild card is provided in the pattern
    const QueryArgument& getPatternSynonym() const;

private:
    QueryArgument patternSynonym;
    bool hasWildCard;
};
