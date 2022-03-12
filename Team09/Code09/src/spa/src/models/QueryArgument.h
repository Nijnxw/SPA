#pragma once

#include <string>
#include "EntityType.h"
#include "AttributeRef.h"

class QueryArgument {
public:
	QueryArgument(const std::string& value, EntityType type, AttributeRef attributeRef = AttributeRef::NONE);
	const std::string& getValue() const;
	EntityType getType() const;
	AttributeRef getAttrRef() const;

	bool operator==(const QueryArgument& other) const {
		return type == other.getType() && value == other.getValue() && attributeRef == other.getAttrRef() ;
	}

private:
	std::string value;  // can either be a literal or variable name (depending on type)
	EntityType type;
	AttributeRef attributeRef;
};

template<>
struct std::hash<QueryArgument> {
	std::size_t operator()(const QueryArgument& arg) const {
		return std::hash<std::string>()(arg.getValue());
	}
};
