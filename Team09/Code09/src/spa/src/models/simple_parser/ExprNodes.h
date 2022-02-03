#pragma once

#include "Node.h"
#include "NodeType.h"

#include <string>
#include <variant>

class VariableNode;
class ConstantNode;
//class OperatorNode;
using ExprNode = std::variant<VariableNode, ConstantNode>;
//using ExprNode = std::variant<VariableNode, ConstantNode, OperatorNode>;

class VariableNode : public Node {
private:
	std::string name;

public:
	VariableNode(std::string s);
	std::string getName();
};

class ConstantNode : public Node {
private:
	std::string value;

public:
	ConstantNode(std::string s);
	std::string getValue();
};