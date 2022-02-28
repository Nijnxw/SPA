#include "AST.h"

ProgramNode::ProgramNode(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap)
: Node(NodeType::PROGRAM) {
	procedureMap = procMap;
}

std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> ProgramNode::getProcedureMap() const {
	return procedureMap;
}

bool ProgramNode::contains(std::string procName) {
	return procedureMap.count(procName) != 0;
}

std::shared_ptr<ProcedureNode> ProgramNode::retrieve(std::string procName) {
	if (!contains(procName)) return nullptr;
	return procedureMap.at(procName);
}

bool ProgramNode::operator==(const Node& other) const {
	const ProgramNode* cast = dynamic_cast<const ProgramNode*>(&other);
	if (cast == nullptr) return false;
	return cast != nullptr &&
		procedureMap == cast->getProcedureMap();
	/*
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> otherProcedureMap = cast->getProcedureMap();
	return cast != nullptr &&
		std::equal(begin(procedureMap), end(procedureMap),
			begin(otherProcedureMap), end(otherProcedureMap),
			[](const std::shared_ptr<ProcedureNode> lhs, const std::shared_ptr<ProcedureNode> rhs) { return *lhs == *rhs; });
	*/
}