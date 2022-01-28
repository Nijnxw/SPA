#include "QueryClause.h"

QueryClause::QueryClause(std::vector<QueryArgument>& arguments) : arguments(arguments) {}

const std::vector<QueryArgument>& QueryClause::GetArguments() const {
    return arguments;
}
