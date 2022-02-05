#include "ExprNodes.h"

// VariableNode Implementation
VariableNode::VariableNode(std::string s)
	: Node(NodeType::VARIABLE) {
	name = s;
}

std::string VariableNode::getName() const {
	return name;
}

bool VariableNode::operator==(const Node& other) const {
	const VariableNode* cast = dynamic_cast<const VariableNode*>(&other);
	return cast != nullptr &&
		name == cast->getName();
}

// ConstantNode Implementation
ConstantNode::ConstantNode(std::string s)
	: Node(NodeType::CONSTANT) {
	value = s;
}

std::string ConstantNode::getValue() const {
	return value;
}

bool ConstantNode::operator==(const Node& other) const {
	const ConstantNode* cast = dynamic_cast<const ConstantNode*>(&other);
	return cast != nullptr &&
		value == cast->getValue();
}

// OperatorNode Implementation
OperatorNode::OperatorNode(BinaryOperator bo, ExprNode left, ExprNode right)
	: Node(NodeType::BINOP), lhs(left), rhs(right) {
	op = bo;
}

BinaryOperator OperatorNode::getOperator() const {
	return op;
}

ExprNode OperatorNode::getLhs() const {
	return lhs;
}

ExprNode OperatorNode::getRhs() const {
	return rhs;
}

bool OperatorNode::operator==(const Node& other) const {
	const OperatorNode* cast = dynamic_cast<const OperatorNode*>(&other);
	return cast != nullptr &&
		op == cast->getOperator() &&
		std::visit(
			[](const auto& thisLhs, const auto& otherLhs) { return *thisLhs == *otherLhs; },
			lhs,
			cast->getLhs()) && 
		std::visit(
			[](const auto& thisRhs, const auto& otherRhs) { return *thisRhs == *otherRhs; },
			rhs,
			cast->getRhs());
}