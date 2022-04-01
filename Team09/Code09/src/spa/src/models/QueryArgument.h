#pragma once

#include <string>
#include "EntityType.h"
#include "AttributeRef.h"

class QueryArgument {
public:
	QueryArgument(const std::string& value, EntityType type, AttributeRef attributeRef = AttributeRef::NONE);
	std::string getValue() const;
	EntityType getType() const;
	AttributeRef getAttrRef() const;
	std::string toString() const;

	bool operator==(const QueryArgument& other) const {
		return type == other.type && value == other.value && attributeRef == other.attributeRef;
	}

private:
	std::string value;  // can either be a literal or variable name (depending on type)
	EntityType type;
	AttributeRef attributeRef;
};

struct QueryArgumentSetEqual {
	bool operator()(const QueryArgument& arg1, const QueryArgument& arg2) const {
		return arg1.getValue() == arg2.getValue();
	}
};

template<>
struct std::hash<QueryArgument> {
	std::size_t operator()(const QueryArgument& arg) const {
		return std::hash<std::string>()(arg.getValue());
	}
};
