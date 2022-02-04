#pragma once

#include "NodeType.h"

class Node {
private:
	NodeType type;

protected:
	Node(NodeType);
	NodeType getNodeType() const;

public:
	virtual ~Node() = default;

	virtual bool operator== (const Node& other) const = 0;
	virtual bool operator!= (const Node& other) const {
		return !(operator==(other));
	}

	virtual bool isIfNode();
	virtual bool isWhileNode();
	virtual bool isAssignNode();
	virtual bool isReadNode();
	virtual bool isPrintNode();
	virtual bool isCallNode();
	virtual bool isVariableNode();
	virtual bool isConstantNode();
	virtual bool isBinOpNode();
	virtual bool isProcedureNode();
	virtual bool isProgramNode();
};