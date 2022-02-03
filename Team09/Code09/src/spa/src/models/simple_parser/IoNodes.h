#pragma once

#include "StmtNode.h"
#include "NodeType.h"
#include "ExprNodes.h"

#include <memory>

class IoNode : public StmtNode {
private:
	std::shared_ptr<VariableNode> variable;

protected:
	IoNode(NodeType t, int sn, std::shared_ptr<VariableNode> var);

public:
	std::shared_ptr<VariableNode> getVariable();
};

class ReadNode : public IoNode {
public:
	ReadNode(int sn, std::shared_ptr<VariableNode> var);
};

class PrintNode : public IoNode {
public:
	PrintNode(int sn, std::shared_ptr<VariableNode> var);
};