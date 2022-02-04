#include "Node.h"

Node::Node(NodeType t) {
	type = t;
}

NodeType Node::getNodeType() const {
	return type;
}

bool Node::isIfNode() {
	return this->getNodeType() == NodeType::IF;
}

bool Node::isWhileNode() {
	return this->getNodeType() == NodeType::WHILE;
}

bool Node::isAssignNode() {
	return this->getNodeType() == NodeType::ASSIGN;
}

bool Node::isReadNode() {
	return this->getNodeType() == NodeType::READ;
}

bool Node::isPrintNode() {
	return this->getNodeType() == NodeType::PRINT;
}

bool Node::isCallNode() {
	return this->getNodeType() == NodeType::CALL;
}

bool Node::isVariableNode() {
	return this->getNodeType() == NodeType::VARIABLE;
}

bool Node::isConstantNode() {
	return this->getNodeType() == NodeType::CONSTANT;
}

bool Node::isBinOpNode() {
	return this->getNodeType() == NodeType::BINOP;
}

bool Node::isProcedureNode() {
	return this->getNodeType() == NodeType::PROCEDURE;
}

bool Node::isProgramNode() {
	return this->getNodeType() == NodeType::PROGRAM;
}