#include "CommonNodes.h"

std::shared_ptr<ConstantNode> CommonNodes::c1 = std::make_shared<ConstantNode>("1");
std::shared_ptr<ConstantNode> CommonNodes::c2 = std::make_shared<ConstantNode>("2");
std::shared_ptr<ConstantNode> CommonNodes::c3 = std::make_shared<ConstantNode>("3");

std::shared_ptr<VariableNode> CommonNodes::a = std::make_shared<VariableNode>("a");
std::shared_ptr<VariableNode> CommonNodes::x = std::make_shared<VariableNode>("x");
std::shared_ptr<VariableNode> CommonNodes::y = std::make_shared<VariableNode>("y");
std::shared_ptr<VariableNode> CommonNodes::z = std::make_shared<VariableNode>("z");

AST CommonNodes::generateAST(std::vector<std::shared_ptr<StmtNode>> stmts) {
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList{ proc };
	return std::make_shared<ProgramNode>(procList);
}
