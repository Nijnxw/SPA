#include "QueryPatternClause.h"

QueryPatternClause::QueryPatternClause(QueryArgument& patternSynonym, std::vector<QueryArgument>& arguments,
                                       bool hasWildCard)
        : QueryClause(arguments), patternSynonym(patternSynonym), hasWildCard(hasWildCard) {}

bool QueryPatternClause::isMatchExact() const {
    return !hasWildCard;
}

const QueryArgument& QueryPatternClause::getPatternSynonym() const {
    return patternSynonym;
}
