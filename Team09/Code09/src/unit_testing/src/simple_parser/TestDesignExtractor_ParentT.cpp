#include "catch.hpp"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/DesignExtractor.h"

#include <memory>
#include <vector>

TEST_CASE("ParentT") {
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
	std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
	ExprNode zero = std::make_shared<ConstantNode>("0");
	ExprNode one = std::make_shared<ConstantNode>("1");
	ExprNode two = std::make_shared<ConstantNode>("2");

	// cond expression
	std::shared_ptr<RelExprNode> xGTZero = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, zero);
	std::shared_ptr<RelExprNode> yGTZero = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, zero);

	// assignment rhs
	ExprNode yPlusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, one);
	ExprNode yPlusTwo = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, two);
	ExprNode yMinusOne = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, y, one);

	SECTION("No nesting - No parent") {
		EntityStager::clear();

		/*
		 *  Test Simple Program
		 *  procedure testProgram {
		 * 1	read x;
		 * 2	print x;
		 * 3	read y;
		 *  }
		 */

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<PrintNode> printX = std::make_shared<PrintNode>(2, x);
		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(3, y);

		// set up stmt list
		std::vector<std::shared_ptr<StmtNode>> stmtList{readX, printX, readY};
		// set up procedure
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};
		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);
		REQUIRE(EntityStager::getStagedParentT().empty());

		EntityStager::clear();
	}

	SECTION("No nesting - Parent exist") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 *  procedure testProgram {
		 * 1	read x;
		 * 2	read y;
		 * 3	if (x > 0) then {
		 * 4		x = y + 1;
		 * 		} else {
		 * 5		x = y + 2;
		 *  	}
		 * 6	while (y > 0) {
		 * 7		y = y - 1;
		 * 		}
		 * 	}
		 */

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(2, y);

		// set up if else block
		std::shared_ptr<PredicateNode> ifPred = std::make_shared<PredicateNode>(xGTZero);
		std::vector<std::shared_ptr<StmtNode>> ifList{std::make_shared<AssignNode>(4, x, yPlusOne, "y 1 +")};
		std::vector<std::shared_ptr<StmtNode>> elseList{std::make_shared<AssignNode>(5, x, yPlusTwo, "y 2 +")};
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(3, ifPred, ifList, elseList);

		// set up while block
		std::shared_ptr<PredicateNode> whilePred = std::make_shared<PredicateNode>(yGTZero);
		std::vector<std::shared_ptr<StmtNode>> whileList{std::make_shared<AssignNode>(7, y, yMinusOne, "y 1 -")};
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(6, whilePred, whileList);

		// set up stmt list
		std::vector<std::shared_ptr<StmtNode>> stmtList{readX, readY, ifs, whiles};
		// set up procedure
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};
		AST ast = std::make_shared<ProgramNode>(procList);

		std::vector<std::pair<int, int>> expectedParentsT{
			{3, 4},
			{3, 5},
			{6, 7}
		};

		DesignExtractor::extractDesignElements(ast);
		std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
		std::sort(actualParentsT.begin(), actualParentsT.end());

		REQUIRE(actualParentsT == expectedParentsT);

		EntityStager::clear();
	}

	SECTION("While nested in if - Parent exist") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 *  procedure testProgram {
		 * 1	read x;
		 * 2	read y;
		 * 3	if (x > 0) then {
		 * 4		x = y + 1;
		 * 5		while (y > 0) {
		 * 6			y = y - 1;
		 * 			}
		 * 		} else {
		 * 7		x = y + 2;
		 *  	}
		 * 	}
		 */

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(2, y);

		// set up while block
		std::shared_ptr<PredicateNode> whilePred = std::make_shared<PredicateNode>(yGTZero);
		std::vector<std::shared_ptr<StmtNode>> whileList{std::make_shared<AssignNode>(6, y, yMinusOne, "y 1 -")};
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(5, whilePred, whileList);

		// set up if else block
		std::shared_ptr<PredicateNode> ifPred = std::make_shared<PredicateNode>(xGTZero);
		std::vector<std::shared_ptr<StmtNode>> ifList{std::make_shared<AssignNode>(4, x, yPlusOne, "y 1 +"), whiles};
		std::vector<std::shared_ptr<StmtNode>> elseList{std::make_shared<AssignNode>(7, x, yPlusTwo, "y 2 +")};
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(3, ifPred, ifList, elseList);

		// set up stmt list
		std::vector<std::shared_ptr<StmtNode>> stmtList{readX, readY, ifs};
		// set up procedure
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};
		AST ast = std::make_shared<ProgramNode>(procList);

		std::vector<std::pair<int, int>> expectedParentsT{
			{3, 4},
			{3, 5},
			{3, 6},
			{3, 7},
			{5, 6}
		};

		DesignExtractor::extractDesignElements(ast);
		std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
		std::sort(actualParentsT.begin(), actualParentsT.end());

		REQUIRE(actualParentsT == expectedParentsT);

		EntityStager::clear();
	}

	SECTION("While nested in else - Parent exist") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 *  procedure testProgram {
		 * 1	read x;
		 * 2	read y;
		 * 3	if (x > 0) then {
		 * 4		x = y + 1;
		 * 		} else {
		 * 5		x = y + 2;
		 * 6		while (y > 0) {
		 * 7			y = y - 1;
		 * 			}
		 *  	}
		 * 	}
		 */

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(2, y);

		// set up while block
		std::shared_ptr<PredicateNode> whilePred = std::make_shared<PredicateNode>(yGTZero);
		std::vector<std::shared_ptr<StmtNode>> whileList{std::make_shared<AssignNode>(7, y, yMinusOne, "y 1 -")};
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(6, whilePred, whileList);

		// set up if else block
		std::shared_ptr<PredicateNode> ifPred = std::make_shared<PredicateNode>(xGTZero);
		std::vector<std::shared_ptr<StmtNode>> ifList{std::make_shared<AssignNode>(4, x, yPlusOne, "y 1 +")};
		std::vector<std::shared_ptr<StmtNode>> elseList{std::make_shared<AssignNode>(5, x, yPlusTwo, "y 2 +"), whiles};
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(3, ifPred, ifList, elseList);

		// set up stmt list
		std::vector<std::shared_ptr<StmtNode>> stmtList{readX, readY, ifs};
		// set up procedure
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};
		AST ast = std::make_shared<ProgramNode>(procList);

		std::vector<std::pair<int, int>> expectedParentsT{
			{3, 4},
			{3, 5},
			{3, 6},
			{3, 7},
			{6, 7}
		};

		DesignExtractor::extractDesignElements(ast);
		std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
		std::sort(actualParentsT.begin(), actualParentsT.end());

		REQUIRE(actualParentsT == expectedParentsT);

		EntityStager::clear();
	}

	SECTION("If nested in while - Parent exist") {
		EntityStager::clear();

		/*
		 * Test Simple Program
		 *  procedure testProgram {
		 * 1	read x;
		 * 2	read y;
		 * 3	while (y > 0) {
		 * 4 		y = y - 1;
		 * 5 		if (x > 0) then {
		 * 6			x = y + 1;
		 * 			} else {
		 * 7			x = y + 2;
		 * 			}
		 *  	}
		 * 	}
		 */

		std::shared_ptr<ReadNode> readX = std::make_shared<ReadNode>(1, x);
		std::shared_ptr<ReadNode> readY = std::make_shared<ReadNode>(2, y);

		// set up if else block
		std::shared_ptr<PredicateNode> ifPred = std::make_shared<PredicateNode>(xGTZero);
		std::vector<std::shared_ptr<StmtNode>> ifList{std::make_shared<AssignNode>(6, x, yPlusOne, "y 1 +")};
		std::vector<std::shared_ptr<StmtNode>> elseList{std::make_shared<AssignNode>(7, x, yPlusTwo, "y 2 +")};
		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(5, ifPred, ifList, elseList);

		// set up while block
		std::shared_ptr<PredicateNode> whilePred = std::make_shared<PredicateNode>(yGTZero);
		std::vector<std::shared_ptr<StmtNode>> whileList{std::make_shared<AssignNode>(4, y, yMinusOne, "y 1 -"), ifs};
		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(3, whilePred, whileList);

		// set up stmt list
		std::vector<std::shared_ptr<StmtNode>> stmtList{readX, readY, whiles};
		// set up procedure
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		// set up program
		std::vector<std::shared_ptr<ProcedureNode>> procList{proc};
		AST ast = std::make_shared<ProgramNode>(procList);

		std::vector<std::pair<int, int>> expectedParentsT{
			{3, 4},
			{3, 5},
			{3, 6},
			{3, 7},
			{5, 6},
			{5, 7}
		};

		DesignExtractor::extractDesignElements(ast);
		std::vector<std::pair<int, int>> actualParentsT = EntityStager::getStagedParentT();
		std::sort(actualParentsT.begin(), actualParentsT.end());

		REQUIRE(actualParentsT == expectedParentsT);

		EntityStager::clear();
	}
}
