#pragma once

#include <string>
#include "QueryArgumentType.h"

class QueryArgument {
public:
    QueryArgument(std::string& value, QueryArgumentType type);

    const std::string& getValue() const;
    QueryArgumentType getType();

private:
    std::string value;
    QueryArgumentType type;
};
