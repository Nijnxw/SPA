#pragma once

#include "QueryArgumentType.h"
#include "QueryArgument.h"
#include "QueryClause.h"
#include "QueryPatternClause.h"

class Query {
public:
    Query(std::vector<QueryArgument>& resultSynonyms, std::vector<QueryClause>& suchThatClauses,
          std::vector<QueryPatternClause>& patternClauses);

    const std::vector<QueryArgument>& GetResultSynonyms() const;
    const std::vector<QueryClause>& GetSuchThatClauses() const;
    const std::vector<QueryPatternClause>& GetPatternClauses() const;

private:
    std::vector<QueryArgument> resultSynonyms;
    std::vector<QueryClause> suchThatClauses;
    std::vector<QueryPatternClause> patternClauses;
};
