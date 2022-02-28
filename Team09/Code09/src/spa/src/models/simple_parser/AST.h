#pragma once

#include "Node.h"
#include "NodeType.h"
#include "ProcedureNode.h"

#include <memory>
#include <string>
#include <unordered_map>

class ProgramNode : public Node {
private:
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procedureMap;

public:
	ProgramNode(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap);
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> getProcedureMap() const;
	bool contains(std::string procName);
	std::shared_ptr<ProcedureNode> retrieve(std::string procName);
	bool operator==(const Node& other) const override;
};

using AST = std::shared_ptr<ProgramNode>;