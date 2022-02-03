#pragma once

#include "StmtNode.h"
#include "NodeType.h"
#include "Node.h"

#include <memory>
#include <string>
#include <vector>

class ProcedureNode : public Node {
private:
	std::vector<std::shared_ptr<StmtNode>> stmtList;
	std::string name;

public:
	ProcedureNode(std::vector<std::shared_ptr<StmtNode>> stList, std::string procName);
	std::vector<std::shared_ptr<StmtNode>> getStmtList();
	std::string getProcName();
};