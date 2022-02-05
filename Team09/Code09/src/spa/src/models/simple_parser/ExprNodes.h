#pragma once

#include "BinaryOperator.h"
#include "Node.h"
#include "NodeType.h"

#include <string>
#include <variant>
#include <memory>

class VariableNode;
class ConstantNode;
class OperatorNode;
using ExprNode = 
	std::variant<std::shared_ptr<VariableNode>, std::shared_ptr<ConstantNode>, std::shared_ptr<OperatorNode>>;

class VariableNode : public Node {
private:
	std::string name;

public:
	VariableNode(std::string s);
	std::string getName() const;
	bool operator==(const Node& other) const override;
};

class ConstantNode : public Node {
private:
	std::string value;

public:
	ConstantNode(std::string s);
	std::string getValue() const;
	bool operator==(const Node& other) const override;
};

class OperatorNode : public Node {
private:
	BinaryOperator op;
	ExprNode lhs;
	ExprNode rhs;

public:
	OperatorNode(BinaryOperator bo, ExprNode left, ExprNode right);
	BinaryOperator getOperator() const;
	ExprNode getLhs() const;
	ExprNode getRhs() const;
	bool operator==(const Node& other) const override;
};