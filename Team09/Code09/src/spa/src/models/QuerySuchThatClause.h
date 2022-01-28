#pragma once

#include "QueryClause.h"
#include "QueryRelationType.h"

class QuerySuchThatClause : public QueryClause {
public:
    QuerySuchThatClause(QueryRelationType& relationType, std::vector<QueryArgument>& arguments);

    const QueryRelationType& GetRelationType() const;

private:
    QueryRelationType relationType;
};
