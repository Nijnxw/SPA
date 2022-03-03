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

	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> otherProcedureMap = cast->getProcedureMap();

	//manual checking
	if (procedureMap.size() != otherProcedureMap.size()) return false;
	for (std::pair<std::string, std::shared_ptr<ProcedureNode>> procPair : procedureMap) {
		//check key
		if (otherProcedureMap.find(procPair.first) == otherProcedureMap.end()) return false;
		//check value
		if (*(procPair.second) != *(otherProcedureMap.at(procPair.first))) return false;
	}
	return true;
}