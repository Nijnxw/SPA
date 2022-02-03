#include "ExprNodes.h"

// VariableNode Implementation
VariableNode::VariableNode(std::string s)
	: Node(NodeType::VARIABLE) {
	name = s;
}

std::string VariableNode::getName() {
	return name;
}

// ConstantNode Implementation
ConstantNode::ConstantNode(std::string s)
	: Node(NodeType::CONSTANT) {
	value = s;
}

std::string ConstantNode::getValue() {
	return value;
}