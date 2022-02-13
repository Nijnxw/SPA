#include "catch.hpp"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
#include <vector>

TEST_CASE("Follows") {
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");

	SECTION ("Basic IO") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	read x;
		 * 2	print x;
		 * }
		 */

		std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(2, x);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{stmt1, stmt2};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollows{{1, 2}};

		REQUIRE(EntityStager::getStagedFollows() == expectedFollows);

		EntityStager::clear();
	}

	SECTION("3 lines - Basic IO") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	read x;
		 * 2	print x;
		 * 3	print y;
		 * }
		 */

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

		std::vector<std::pair<int, int>> expectedFollows{
			{1, 2},
			{2, 3}
		};

		REQUIRE(EntityStager::getStagedFollows() == expectedFollows);

		EntityStager::clear();
	}
}

TEST_CASE("Follows - With Assignment") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	read x;
	 * 2	x = y + 1;
	 * }
	 */

	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	ExprNode y = std::make_shared<VariableNode>("y");
	ExprNode one = std::make_shared<ConstantNode>("1");

	std::shared_ptr<ReadNode> stmt1 = std::make_shared<ReadNode>(1, x);

	ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);
	std::shared_ptr<AssignNode> stmt2 = std::make_shared<AssignNode>(2, x, expression, "y 1 +");

	// set up procedure
	std::vector<std::shared_ptr<StmtNode>> stmtList{stmt1, stmt2};
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	// set up program
	std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollows{{1, 2}};

	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);

	EntityStager::clear();
}

TEST_CASE("Follows - With While") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	while (x > 1) {
	 * 2	    read x;
	 * 3        read z;
	 *      }
	 * 4    read y;
	 * }
	 */

	// building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
	std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

	std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
	std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

	std::shared_ptr<ReadNode> read1 = std::make_shared<ReadNode>(2, x);
	std::shared_ptr<ReadNode> read2 = std::make_shared<ReadNode>(3, z);
	std::vector<std::shared_ptr<StmtNode>> whileStmtList{read1, read2};
	std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

	std::shared_ptr<ReadNode> read3 = std::make_shared<ReadNode>(4, y);

	// set up procedure
	std::vector<std::shared_ptr<StmtNode>> stmtList{whiles, read3};
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	// set up program
	std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);

	std::vector<std::pair<int, int>> expectedFollows{
		{1, 4},
		{2, 3}
	};

	REQUIRE(EntityStager::getStagedFollows() == expectedFollows);

	EntityStager::clear();
}

TEST_CASE("Follows - With If") {
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
	RelFactorNode one = std::make_shared<ConstantNode>("1");

	// cond expression
	std::shared_ptr<RelExprNode> yGTOne = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);

	SECTION("Single if - simple predicate") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        read x;
		 *      } else {
		 * 3        print z;
		 *      }
		 * 4    read y;
		 *  }
		 */

		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(yGTOne);

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(2, x);
		std::vector<std::shared_ptr<StmtNode>> thenStmtList{readX};
		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(3, z);
		std::vector<std::shared_ptr<StmtNode>> elseStmtList{print};

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);

		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(4, y);

		// set up procedure
		std::vector<std::shared_ptr<StmtNode>> stmtList{ifs, readY};
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, int>> expectedFollows{
			{1, 4}
		};

		REQUIRE(EntityStager::getStagedFollows() == expectedFollows);

		DesignExtractor::extractDesignElements(ast);

		EntityStager::clear();
	}
}