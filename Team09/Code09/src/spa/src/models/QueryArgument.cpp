#include <string>
#include "QueryArgument.h"

QueryArgument::QueryArgument(std::string& value, QueryArgumentType type) : value(value), type(type) {}

const std::string& QueryArgument::getValue() const {
    return value;
}

QueryArgumentType QueryArgument::getType() {
    return type;
}
