#include <string>
#include "QueryArgument.h"

QueryArgument::QueryArgument(std::string& value, EntityType type) : value(value), type(type) {}

const std::string& QueryArgument::getValue() const {
    return value;
}

EntityType QueryArgument::getType() {
    return type;
}
