#include "ExprNodes.h"

// VariableNode Implementation
VariableNode::VariableNode(std::string s)
	: Node(NodeType::Variable) {
	name = s;
}

std::string VariableNode::getName() {
	return name;
}

// ConstantNode Implementation
ConstantNode::ConstantNode(std::string s)
	: Node(NodeType::Constant) {
	value = s;
}

std::string ConstantNode::getValue() {
	return value;
}