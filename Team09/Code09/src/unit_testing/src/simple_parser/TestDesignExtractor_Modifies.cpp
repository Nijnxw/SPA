#include "catch.hpp"
#include "models/EntityType.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

TEST_CASE("Modifies - Read Statement") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	read x;
	 * }
	 */

	 // building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");

	std::shared_ptr<ReadNode> stmt = std::make_shared<ReadNode>(1, x);

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt);

	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
	std::unordered_set<std::string> vars;
	vars.insert("x");
	expectedModifies.push_back(std::make_pair(1, vars));

	REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

	EntityStager::clear();
}

TEST_CASE("Modifies - Assign Statement") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	x = y + 1;
	 * }
	 */
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");

	ExprNode y = std::make_shared<VariableNode>("y");
	ExprNode one = std::make_shared<ConstantNode>("1");
	ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);

	std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, expression, "y 1 +");

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt);

	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
	std::unordered_set<std::string> vars{ "x" };
	expectedModifies.push_back(std::make_pair(1, vars));

	REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

	EntityStager::clear();
}