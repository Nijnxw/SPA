
#include <vector>
#include "QueryArgument.h"
#include "QueryRelationType.h"
#include "QuerySuchThatClause.h"

QuerySuchThatClause::QuerySuchThatClause(QueryRelationType& relationType, std::vector<QueryArgument>& arguments)
        : relationType(relationType), QueryClause(arguments) {}

const QueryRelationType& QuerySuchThatClause::getRelationType() const {
    return relationType;
}
