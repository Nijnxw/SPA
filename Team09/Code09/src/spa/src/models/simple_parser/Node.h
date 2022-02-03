#pragma once

#include "NodeType.h"

class Node {
private:
	NodeType type;

protected:
	Node(NodeType);
	NodeType getNodeType() const;

public:
	bool isIfNode();
	bool isWhileNode();
	bool isAssignNode();
	bool isReadNode();
	bool isPrintNode();
	bool isCallNode();
	bool isVariableNode();
	bool isConstantNode();
	bool isBinOpNode();
	bool isProcedureNode();
	bool isRootNode();
};