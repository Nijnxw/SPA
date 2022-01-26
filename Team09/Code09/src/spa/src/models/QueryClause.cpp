#include "QueryClause.h"
#include "QueryArgumentType.h"

QueryClause::QueryClause(QueryArgumentType& clauseType, std::vector<QueryArgument>& arguments) : clauseType(clauseType),
                                                                                                 arguments(arguments) {}

QueryArgumentType QueryClause::GetClauseType() const {
    return clauseType;
}

const std::vector<QueryArgument>& QueryClause::GetArguments() const {
    return arguments;
}
