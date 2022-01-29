#pragma once

#include "QueryArgument.h"
#include "QueryPatternClause.h"
#include "QuerySuchThatClause.h"

class Query {
public:
    Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QuerySuchThatClause>& suchThatClauses,
          std::vector<QueryPatternClause>& patternClauses);

    const std::vector<QueryArgument>& getResultSynonyms() const;
    const std::vector<QuerySuchThatClause>& getSuchThatClauses() const;
    const std::vector<QueryPatternClause>& getPatternClauses() const;

private:
    std::vector<QueryArgument> resultSynonyms;
    std::vector<QuerySuchThatClause> suchThatClauses;
    std::vector<QueryPatternClause> patternClauses;
};
