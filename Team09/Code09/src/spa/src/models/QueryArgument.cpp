#include <string>
#include "QueryArgument.h"

QueryArgument::QueryArgument(const std::string& value, EntityType type, AttributeRef attributeRef) 
	: value(value), type(type), attributeRef(attributeRef) {}

const std::string& QueryArgument::getValue() const {
    return value;
}

EntityType QueryArgument::getType() const {
	return type;
}

AttributeRef QueryArgument::getAttrRef() const {
	return attributeRef;
}
