#include "catch.hpp"
#include "models/EntityType.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
#include <unordered_set>
#include <vector>

TEST_CASE("Basic Follows* - 3 lines - IO") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	read x;
	 * 2	print x;
	 * 3	print y;
	 * }
	 */

	 // building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, x);
	std::shared_ptr<PrintNode> stmt3 = std::make_shared<PrintNode>(3, y);

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt1);
	stmtList.push_back(stmt2);
	stmtList.push_back(stmt3);

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc1);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollowsT;
	expectedFollowsT.push_back(std::make_pair(1, 2));
	expectedFollowsT.push_back(std::make_pair(1, 3));
	expectedFollowsT.push_back(std::make_pair(2, 3));

	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

	EntityStager::clear();
}

TEST_CASE("Basic Follows* - 3 lines - With Assignment") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	read x;
	 * 2	print y;
	 * 3	y = x + 1;
	 * }
	 */

	 // building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, y);

	ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
	std::shared_ptr<AssignNode> stmt3 = std::make_shared<AssignNode>(3, y, expression, "x 1 +");

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt1);
	stmtList.push_back(stmt2);
	stmtList.push_back(stmt3);

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc1);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollowsT{
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(2, 3)
	};

	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

	EntityStager::clear();
}

TEST_CASE("Follows* - 3 statements - With While") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	while (x > 1) {
	 * 2	    read x;
	 * 3        read z;
	 * 4    	y = x + 1;
	 *      }
	 * 5    read y;
	 * }
	 */

	 // building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
	std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

	std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
	std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

	std::vector<std::shared_ptr<StmtNode>> whileStmtList;
	std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(2, x);
	std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(3, z);
	ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
	std::shared_ptr<AssignNode> stmt3 = std::make_shared<AssignNode>(4, y, expression, "x 1 +");
	whileStmtList.push_back(read1);
	whileStmtList.push_back(read2);
	whileStmtList.push_back(stmt3);

	std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);
	std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(5, y);
	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(whiles);
	stmtList.push_back(read3);

	std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc1);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> test = EntityStager::getStagedFollowsT();

	std::vector<std::pair<int, int>> expectedFollowsT{
		std::make_pair(1, 5),
		std::make_pair(2, 3),
		std::make_pair(2, 4),
		std::make_pair(3, 4)
	};

	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

	EntityStager::clear();
}