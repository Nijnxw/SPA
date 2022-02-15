#include "RelationshipASTs.h"

// construction helpers
std::shared_ptr<VariableNode> generateVariable(std::string varName) {
	return std::make_shared<VariableNode>(varName);
}

std::shared_ptr<ConstantNode> generateConstant(std::string conValue) {
	return std::make_shared<ConstantNode>(conValue);
}

AST generateAST(std::vector<std::shared_ptr<StmtNode>> stmts, std::string progName) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, progName);
	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
	return std::make_shared<ProgramNode>(procList);
}

AST RelationshipASTs::getAST3_5() {
	std::vector<std::shared_ptr<StmtNode>> stmtList{
		std::make_shared<ReadNode>(1, generateVariable("x")),
		std::make_shared<PrintNode>(2, generateVariable("x"))
	};
	return generateAST(stmtList, "testProgram");
}