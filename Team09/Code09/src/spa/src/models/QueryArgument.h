#pragma once

#include <string>
#include "EntityType.h"

class QueryArgument {
public:
	QueryArgument(const std::string& value, EntityType type);

	const std::string& getValue() const;
	EntityType getType() const;

	bool operator==(const QueryArgument& other) const {
		return type == other.getType() && value == other.getValue();
	}

private:
	std::string value;  // can either be a literal or variable name (depending on type)
	EntityType type;
};

template<>
struct std::hash<QueryArgument> {
	std::size_t operator()(const QueryArgument& arg) const {
		return std::hash<std::string>()(arg.getValue());
	}
};
