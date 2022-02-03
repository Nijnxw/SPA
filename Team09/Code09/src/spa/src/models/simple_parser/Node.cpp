#include "Node.h"

Node::Node(NodeType t) {
	type = t;
}

NodeType Node::getNodeType() const {
	return type;
}

bool Node::isIfNode() {
	return this->getNodeType() == NodeType::If;
}

bool Node::isWhileNode() {
	return this->getNodeType() == NodeType::While;
}

bool Node::isAssignNode() {
	return this->getNodeType() == NodeType::Assign;
}

bool Node::isReadNode() {
	return this->getNodeType() == NodeType::Read;
}

bool Node::isPrintNode() {
	return this->getNodeType() == NodeType::Print;
}

bool Node::isCallNode() {
	return this->getNodeType() == NodeType::Call;
}

bool Node::isVariableNode() {
	return this->getNodeType() == NodeType::Variable;
}

bool Node::isConstantNode() {
	return this->getNodeType() == NodeType::Constant;
}

bool Node::isBinOpNode() {
	return this->getNodeType() == NodeType::BinOp;
}

bool Node::isProcedureNode() {
	return this->getNodeType() == NodeType::Procedure;
}

bool Node::isRootNode() {
	return this->getNodeType() == NodeType::Root;
}