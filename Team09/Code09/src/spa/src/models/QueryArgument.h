#pragma once

#include <string>
#include "EntityType.h"

class QueryArgument {
public:
    QueryArgument(std::string& value, EntityType type);

    const std::string& getValue() const;
    EntityType getType();

private:
    std::string value;  // can either be a literal or variable name (depending on type)
    EntityType type;
};
