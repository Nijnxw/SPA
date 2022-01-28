#include <vector>
#include "Query.h"

Query::Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QuerySuchThatClause>& suchThatClauses,
             std::vector<QueryPatternClause>& patternClauses) : resultSynonyms(resultSynonyms),
                                                                suchThatClauses(suchThatClauses),
                                                                patternClauses(patternClauses) {}

const std::vector<QueryArgument>& Query::getResultSynonyms() const {
    return resultSynonyms;
}

const std::vector<QuerySuchThatClause>& Query::getSuchThatClauses() const {
    return suchThatClauses;
}

const std::vector<QueryPatternClause>& Query::getPatternClauses() const {
    return patternClauses;
}
