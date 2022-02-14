#include "catch.hpp"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
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

	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, x);
	std::shared_ptr<PrintNode> stmt3 = std::make_shared<PrintNode>(3, y);

	// set up procedure
	std::vector<std::shared_ptr<StmtNode>> stmtList{stmt1, stmt2, stmt3};
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	// set up program
	std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollowsT{
		{1, 2},
		{1, 3},
		{2, 3}
	};

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

	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
	std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, y);

	ExprNode xPlusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
	std::shared_ptr<AssignNode> stmt3 = std::make_shared<AssignNode>(3, y, xPlusOne, "x 1 +");

	// set up procedure
	std::vector<std::shared_ptr<StmtNode>> stmtList{stmt1, stmt2, stmt3};
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	// set up program
	std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollowsT{
		{1, 2},
		{1, 3},
		{2, 3}
	};

	REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

	EntityStager::clear();
}

TEST_CASE("Follows* - 3 statements - With While") {
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
	std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

	// cond expression
	std::shared_ptr<RelExprNode> yGTOne = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
	std::shared_ptr<RelExprNode> yLTZ = std::make_shared<RelExprNode>(y, ComparatorOperator::LT, z);

	// assignment rhs
	ExprNode xPlusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
	ExprNode yPlusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);

	SECTION("while no nesting") {
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

		// set up while block
		std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(2, x);
		std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(3, z);
		std::shared_ptr<AssignNode> stmt3 = std::make_shared<AssignNode>(4, y, xPlusOne, "x 1 +");
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{read1, read2, stmt3};
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(yGTOne);
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(5, y);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{whiles, read3};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollowsT{
			{1, 5},
			{2, 3},
			{2, 4},
			{3, 4}
		};

		std::vector<std::pair<int, int>> test = EntityStager::getStagedFollowsT();

		REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

		EntityStager::clear();
	}

	SECTION("while with nesting") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (x > 1) {
		 * 2	    read x;
		 * 3        read z;
		 * 4    	y = x + 1;
		 * 5		while (y < z) {
		 * 6			y = y + 1;
		 * 			}
		 *      }
		 * 7    read y;
		 * }
		 */

		// set up inner while block
		std::shared_ptr<AssignNode> stmt4 = std::make_shared<AssignNode>(6, y, yPlusOne, "y 1 +");
		std::vector<std::shared_ptr<StmtNode>> innerWhileStmtList{stmt4};
		std::shared_ptr<PredicateNode> pred2 = std::make_shared<PredicateNode>(yLTZ);
		std::shared_ptr<WhileNode> whiles2 = std::make_shared<WhileNode>(5, pred2, innerWhileStmtList);

		// set up outer while block
		std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(2, x);
		std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(3, z);
		std::shared_ptr<AssignNode> stmt3 = std::make_shared<AssignNode>(4, y, xPlusOne, "x 1 +");
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{read1, read2, stmt3, whiles2};
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(yGTOne);
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(7, y);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{whiles, read3};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollowsT{
			{1, 7},
			{2, 3},
			{2, 4},
			{2, 5},
			{3, 4},
			{3, 5},
			{4, 5}
		};

		std::vector<std::pair<int, int>> test = EntityStager::getStagedFollowsT();

		REQUIRE(EntityStager::getStagedFollowsT() == expectedFollowsT);

		EntityStager::clear();
	}
}

TEST_CASE("Follows* - With If") {
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	RelFactorNode one = std::make_shared<ConstantNode>("1");

	// cond expression
	std::shared_ptr<RelExprNode> yGTOne = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
	std::shared_ptr<RelExprNode> yLTX = std::make_shared<RelExprNode>(y, ComparatorOperator::LT, x);

	// assignment rhs
	ExprNode yPlusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);

	SECTION("Single if - simple predicate") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        read x;
		 * 3        read x;
		 * 4        read x;
		 *      } else {
		 *      }
		 * 5    read y;
		 * 6    read y;
		 * 7    read y;
		 *  }
		 */

		// set up if else block
		std::shared_ptr<ReadNode> readX2 = std::make_shared<ReadNode>(2, x);
		std::shared_ptr<ReadNode> readX3 = std::make_shared<ReadNode>(3, x);
		std::shared_ptr<ReadNode> readX4 = std::make_shared<ReadNode>(4, x);
		std::vector<std::shared_ptr<StmtNode>> thenStmtList{readX2, readX3, readX4};
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(yGTOne);
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);

		std::shared_ptr<ReadNode> readY5 = std::make_shared<ReadNode>(5, y);
		std::shared_ptr<ReadNode> readY6 = std::make_shared<ReadNode>(6, y);
		std::shared_ptr<ReadNode> readY7 = std::make_shared<ReadNode>(7, y);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{ifs, readY5, readY6, readY7};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollows{
			{1, 5},
			{1, 6},
			{1, 7},
			{2, 3},
			{2, 4},
			{3, 4},
			{5, 6},
			{5, 7},
			{6, 7}
		};

		std::vector<std::pair<int, int>> test = EntityStager::getStagedFollowsT();

		REQUIRE(EntityStager::getStagedFollowsT() == expectedFollows);

		DesignExtractor::extractDesignElements(ast);

		EntityStager::clear();
	}

	SECTION("nested if - simple predicate") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        read x;
		 * 3        read x;
		 * 4		if (y < x) then {
		 * 5			y = y + 1;
		 * 			} else {
		 * 			}
		 * 6        read x;
		 *      } else {
		 *      }
		 * 7    read y;
		 * 8    read y;
		 * 9    read y;
		 *  }
		 */

		// set up inner if else block
		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(5, y, yPlusOne, "y 1 +");
		std::vector<std::shared_ptr<StmtNode>> innerThenStmtList{stmt};
		std::vector<std::shared_ptr<StmtNode>> innerElseStmtList;
		std::shared_ptr<PredicateNode> pred2 = std::make_shared<PredicateNode>(yLTX);
		std::shared_ptr<IfNode> ifs2 = std::make_shared<IfNode>(4, pred2, innerThenStmtList, innerElseStmtList);

		// set up outer if else block
		std::shared_ptr<ReadNode> readX2 = std::make_shared<ReadNode>(2, x);
		std::shared_ptr<ReadNode> readX3 = std::make_shared<ReadNode>(3, x);
		std::shared_ptr<ReadNode> readX4 = std::make_shared<ReadNode>(6, x);
		std::vector<std::shared_ptr<StmtNode>> thenStmtList{readX2, readX3, ifs2, readX4};
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
		std::shared_ptr<PredicateNode> pred1 = std::make_shared<PredicateNode>(yGTOne);
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred1, thenStmtList, elseStmtList);

		std::shared_ptr<ReadNode> readY5 = std::make_shared<ReadNode>(7, y);
		std::shared_ptr<ReadNode> readY6 = std::make_shared<ReadNode>(8, y);
		std::shared_ptr<ReadNode> readY7 = std::make_shared<ReadNode>(9, y);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{ifs, readY5, readY6, readY7};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollows{
			{1, 7},
			{1, 8},
			{1, 9},
			{2, 3},
			{2, 4},
			{2, 6},
			{3, 4},
			{3, 6},
			{4, 6},
			{7, 8},
			{7, 9},
			{8, 9}
		};

		std::vector<std::pair<int, int>> test = EntityStager::getStagedFollowsT();

		REQUIRE(EntityStager::getStagedFollowsT() == expectedFollows);

		DesignExtractor::extractDesignElements(ast);

		EntityStager::clear();
	}
}