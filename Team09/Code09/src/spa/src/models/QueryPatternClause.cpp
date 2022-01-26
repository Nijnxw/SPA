#include "QueryPatternClause.h"

QueryPatternClause::QueryPatternClause(QueryArgumentType& clauseType, std::vector<QueryArgument>& arguments,
                                       QueryArgument& patternSynonym, bool isMatchExact)
        : QueryClause(clauseType, arguments), patternSynonym(patternSynonym), isMatchExact(isMatchExact) {}

bool QueryPatternClause::IsMatchExact() const {
    return isMatchExact;
}

const QueryArgument& QueryPatternClause::GetPatternSynonym() const {
    return patternSynonym;
}
