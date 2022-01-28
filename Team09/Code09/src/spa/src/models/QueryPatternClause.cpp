#include "QueryPatternClause.h"

QueryPatternClause::QueryPatternClause(QueryArgument& patternSynonym, std::vector<QueryArgument>& arguments,
                                       bool isMatchExact)
        : QueryClause(arguments), patternSynonym(patternSynonym), isMatchExact(isMatchExact) {}

bool QueryPatternClause::IsMatchExact() const {
    return isMatchExact;
}

const QueryArgument& QueryPatternClause::GetPatternSynonym() const {
    return patternSynonym;
}
