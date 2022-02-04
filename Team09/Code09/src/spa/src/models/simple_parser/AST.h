#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ProcedureNode.h"

#include <memory>
#include <vector>

class ProgramNode : public Node {
private:
	std::vector<std::shared_ptr<ProcedureNode>> procedureList;

public:
	ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procList);
	std::vector<std::shared_ptr<ProcedureNode>> getProcedureList() const;
	bool operator==(const Node& other) const override;
};

using AST = std::shared_ptr<ProgramNode>;