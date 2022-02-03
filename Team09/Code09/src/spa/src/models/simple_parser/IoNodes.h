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
	std::shared_ptr<VariableNode> getVariable() const;
};

class ReadNode : public IoNode {
public:
	ReadNode(int sn, std::shared_ptr<VariableNode> var);
	bool operator==(const Node& other) const override;
};

class PrintNode : public IoNode {
public:
	PrintNode(int sn, std::shared_ptr<VariableNode> var);
	bool operator==(const Node& other) const override;
};