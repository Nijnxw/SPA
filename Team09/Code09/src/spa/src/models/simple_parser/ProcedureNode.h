#pragma once

#include "StmtNode.h"
#include "NodeType.h"
#include "Node.h"

#include <vector>

class ProcedureNode : public Node {
private:
	std::vector<StmtNode> stmtList;

public:
	ProcedureNode(std::vector<StmtNode> stList);
	std::vector<StmtNode> getStmtList();
};