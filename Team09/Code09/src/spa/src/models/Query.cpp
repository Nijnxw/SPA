#include <vector>
#include "Query.h"

Query::Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QueryClause>& suchThatClauses,
             std::vector<QueryPatternClause>& patternClauses) : resultSynonyms(resultSynonyms),
                                                                suchThatClauses(suchThatClauses),
                                                                patternClauses(patternClauses) {}

const std::vector<QueryArgument>& Query::GetResultSynonyms() const {
    return resultSynonyms;
}

const std::vector<QueryClause>& Query::GetSuchThatClauses() const {
    return suchThatClauses;
}

const std::vector<QueryPatternClause>& Query::GetPatternClauses() const {
    return patternClauses;
}
