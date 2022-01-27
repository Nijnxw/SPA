#pragma once

#include "QueryArgument.h"
#include "QueryPatternClause.h"
#include "QuerySuchThatClause.h"

class Query {
public:
    Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QuerySuchThatClause>& suchThatClauses,
          std::vector<QueryPatternClause>& patternClauses);

    const std::vector<QueryArgument>& GetResultSynonyms() const;
    const std::vector<QuerySuchThatClause>& GetSuchThatClauses() const;
    const std::vector<QueryPatternClause>& GetPatternClauses() const;

private:
    std::vector<QueryArgument> resultSynonyms;
    std::vector<QuerySuchThatClause> suchThatClauses;
    std::vector<QueryPatternClause> patternClauses;
};
