#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ProcedureNode.h"

#include <vector>

class RootNode : public Node {
private:
	std::vector<std::shared_ptr<ProcedureNode>> procedureList;

public:
	RootNode(std::vector<std::shared_ptr<ProcedureNode>> procList);
	std::vector<std::shared_ptr<ProcedureNode>> getProcedureList();
};