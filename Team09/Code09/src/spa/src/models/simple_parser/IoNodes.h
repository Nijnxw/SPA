#pragma once

#include "StmtNode.h"
#include "NodeType.h"
#include "ExprNodes.h"

class IoNode : public StmtNode {
private:
	VariableNode variable;

protected:
	IoNode(NodeType t, int sn, VariableNode var);

public:
	VariableNode getVariable();
};

class ReadNode : public IoNode {
public:
	ReadNode(int sn, VariableNode var);
};

class PrintNode : public IoNode {
public:
	PrintNode(int sn, VariableNode var);
};