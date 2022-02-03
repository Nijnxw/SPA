#pragma once

#include "StmtNode.h"
#include "NodeType.h"
#include "Node.h"

#include <memory>
#include <vector>

class ProcedureNode : public Node {
private:
	std::vector<std::shared_ptr<StmtNode>> stmtList;

public:
	ProcedureNode(std::vector<std::shared_ptr<StmtNode>> stList);
	std::vector<std::shared_ptr<StmtNode>> getStmtList();
};