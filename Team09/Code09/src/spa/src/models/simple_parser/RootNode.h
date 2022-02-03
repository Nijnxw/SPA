#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ProcedureNode.h"

#include <vector>

class RootNode : public Node {
private:
	std::vector<ProcedureNode> procedureList;

public:
	RootNode(std::vector<ProcedureNode> procList);
	std::vector<ProcedureNode> getProcedureList();
};