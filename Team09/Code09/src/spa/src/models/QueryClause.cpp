#include "QueryClause.h"

QueryClause::QueryClause(std::vector<QueryArgument>& arguments) : arguments(arguments) {}

const std::vector<QueryArgument>& QueryClause::getArguments() const {
    return arguments;
}
