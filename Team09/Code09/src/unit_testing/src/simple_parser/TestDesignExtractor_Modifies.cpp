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
	SECTION("Assign Statement with variables one sides") {
		EntityStager::clear();
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = 1;
		 * }
		 */
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		ExprNode one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, one, "x 1 +");

		std::vector<std::shared_ptr<StmtNode>> stmtList;
		stmtList.push_back(stmt);

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> assign{ "x" };
		expectedModifies.push_back(std::make_pair(1, assign));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Assign Statement with variables both sides") {
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
}

TEST_CASE("Modifies - While Statement") {
	EntityStager::clear();

	SECTION("Single While loop - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::vector<std::shared_ptr<StmtNode>> whileStmtList;

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Single While loop - simple predicate - read statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2        read x;
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, x);
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{ read };

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> whileModifies{ "x" };
		std::unordered_set<std::string> readModifies{ "x" };
		expectedModifies.push_back(std::make_pair(2, readModifies));
		expectedModifies.push_back(std::make_pair(1, whileModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Single While loop - simple predicate - assign statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2    	y = x + 1;
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(2, y, expression, "y 1 +");
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{ assign };

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> whileModifies{ "y" };
		std::unordered_set<std::string> assignModifies{ "y" };
		expectedModifies.push_back(std::make_pair(2, assignModifies));
		expectedModifies.push_back(std::make_pair(1, whileModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	//todo: everything in between
	SECTION("Single While loop - complex predicate - multiple lines") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y + 2 > z - 1 && a == 123) {
		 * 2    	d = d + 1;
		 * 3        print c;
		 * 4        read b;
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> a = std::make_shared<VariableNode>("a");
		std::shared_ptr<VariableNode> b = std::make_shared<VariableNode>("b");
		std::shared_ptr<VariableNode> c = std::make_shared<VariableNode>("c");
		std::shared_ptr<VariableNode> d = std::make_shared<VariableNode>("d");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");
		std::shared_ptr<ConstantNode> two = std::make_shared<ConstantNode>("2");
		std::shared_ptr<ConstantNode> onetwothree = std::make_shared<ConstantNode>("123");

		std::shared_ptr<BinaryOperatorNode> leftRelLhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, two);
		std::shared_ptr<BinaryOperatorNode> leftRelRhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, z, one);

		std::shared_ptr<RelExprNode> leftRel = std::make_shared<RelExprNode>(leftRelLhs, ComparatorOperator::GT, leftRelRhs);
		std::shared_ptr<RelExprNode> rightRel = std::make_shared<RelExprNode>(a, ComparatorOperator::EQ, onetwothree);

		std::shared_ptr<PredicateNode> leftPred = std::make_shared<PredicateNode>(leftRel);
		std::shared_ptr<PredicateNode> rightPred = std::make_shared<PredicateNode>(rightRel);

		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(leftPred, ConditionalOperator::AND, rightPred);

		std::vector<std::shared_ptr<StmtNode>> whileStmtList;
		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, d, one);
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(2, d, expression, "d 1 +");
		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(3, c);
		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(4, b);
		whileStmtList.push_back(assign);
		whileStmtList.push_back(print);
		whileStmtList.push_back(read);

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> whileModifies{ "d", "b" };
		std::unordered_set<std::string> assignModifies{ "d" };
		std::unordered_set<std::string> readModifies{ "b" };
		expectedModifies.push_back(std::make_pair(2, assignModifies));
		expectedModifies.push_back(std::make_pair(4, readModifies));
		expectedModifies.push_back(std::make_pair(1, whileModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Double Nested While loop - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2        while (x > 1) {
		 * 3            d = d + 1;
		 *          }
		 * 4        read z;
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> d = std::make_shared<VariableNode>("d");
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);

		std::vector<std::shared_ptr<StmtNode>> outerWhileStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerWhileStmtList;

		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, d, one);
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(3, d, expression, "d 1 +");
		innerWhileStmtList.push_back(assign);

		std::shared_ptr<WhileNode> innerWhile = std::make_shared<WhileNode>(2, innerPred, innerWhileStmtList);
		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(4, z);
		outerWhileStmtList.push_back(innerWhile);
		outerWhileStmtList.push_back(read);

		std::shared_ptr<WhileNode> outerWhile = std::make_shared<WhileNode>(1, outerPred, outerWhileStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ outerWhile };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> assignModifies{ "d" };
		std::unordered_set<std::string> readModifies{ "z" };
		std::unordered_set<std::string> innerWhileModifies{ "d" };
		std::unordered_set<std::string> outerWhileModifies{ "d", "z" };
		expectedModifies.push_back(std::make_pair(3, assignModifies));
		expectedModifies.push_back(std::make_pair(2, innerWhileModifies));
		expectedModifies.push_back(std::make_pair(4, readModifies));
		expectedModifies.push_back(std::make_pair(1, outerWhileModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}
}

TEST_CASE("Modifies - If Statement") {
	EntityStager::clear();

	SECTION("Single If - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {} else {}
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Single if - simple predicate - read statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        read z;
		 *      } else {}
		 * }
		 */
		 // building AST
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(2, z);
		thenStmtList.push_back(read);

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> readModifies{ "z" };
		std::unordered_set<std::string> ifModifies{ "z" };
		expectedModifies.push_back(std::make_pair(2, readModifies));
		expectedModifies.push_back(std::make_pair(1, ifModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Single If - simple predicate - assign statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        z = z + 1
		 *      } else {}
		 * 3    x = x + 1;
		 * }
		 */
		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
		ExprNode expressionZ = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, z, one);
		std::shared_ptr<AssignNode> assignZ = std::make_shared<AssignNode>(2, z, expressionZ, "z 1 +");
		thenStmtList.push_back(assignZ);

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);
		ExprNode expressionX = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, one);
		std::shared_ptr<AssignNode> assignX = std::make_shared<AssignNode>(3, x, expressionX, "x 1 +");
		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs, assignX };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> innerAssignModifies{ "z" };
		std::unordered_set<std::string> outsideAssignModifies{ "x" };
		std::unordered_set<std::string> ifModifies{ "z" };
		expectedModifies.push_back(std::make_pair(2, innerAssignModifies));
		expectedModifies.push_back(std::make_pair(1, ifModifies));
		expectedModifies.push_back(std::make_pair(3, outsideAssignModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	//todo: everything in between
	SECTION("Single If - complex predicate - multiple lines") {
		/*
		* Test Simple Program
		* procedure testProgram {
		* 1    if (y + 2 > z - 1 && a == 123) then {
		*      } else {
		* 2        d = d + 1;
		* 3        print c;
		* 4        read b;
		*      }
		* }
		*/

		// building AST
		std::shared_ptr<VariableNode> a = std::make_shared<VariableNode>("a");
		std::shared_ptr<VariableNode> b = std::make_shared<VariableNode>("b");
		std::shared_ptr<VariableNode> c = std::make_shared<VariableNode>("c");
		std::shared_ptr<VariableNode> d = std::make_shared<VariableNode>("d");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");
		std::shared_ptr<ConstantNode> two = std::make_shared<ConstantNode>("2");
		std::shared_ptr<ConstantNode> onetwothree = std::make_shared<ConstantNode>("123");

		std::shared_ptr<BinaryOperatorNode> leftRelLhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, y, two);
		std::shared_ptr<BinaryOperatorNode> leftRelRhs = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS, z, one);

		std::shared_ptr<RelExprNode> leftRel = std::make_shared<RelExprNode>(leftRelLhs, ComparatorOperator::GT, leftRelRhs);
		std::shared_ptr<RelExprNode> rightRel = std::make_shared<RelExprNode>(a, ComparatorOperator::EQ, onetwothree);

		std::shared_ptr<PredicateNode> leftPred = std::make_shared<PredicateNode>(leftRel);
		std::shared_ptr<PredicateNode> rightPred = std::make_shared<PredicateNode>(rightRel);

		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(leftPred, ConditionalOperator::AND, rightPred);

		std::vector<std::shared_ptr<StmtNode>> thenStmtList;
		std::vector<std::shared_ptr<StmtNode>> elseStmtList;
		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, d, one);
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(2, d, expression, "d 1 +");
		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(3, c);
		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(4, b);
		elseStmtList.push_back(assign);
		elseStmtList.push_back(print);
		elseStmtList.push_back(read);

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, pred, thenStmtList, elseStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> ifModifies{ "d", "b" };
		std::unordered_set<std::string> assignModifies{ "d" };
		std::unordered_set<std::string> readModifies{ "b" };
		expectedModifies.push_back(std::make_pair(2, assignModifies));
		expectedModifies.push_back(std::make_pair(4, readModifies));
		expectedModifies.push_back(std::make_pair(1, ifModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}

	SECTION("Double Nested if - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        if (x > 1) then {
		 * 3            d = d + 1;
		 *          } else {}
		 * 4        read z;
		 *      } else {}
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> d = std::make_shared<VariableNode>("d");
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);

		std::vector<std::shared_ptr<StmtNode>> outerThenStmtList;
		std::vector<std::shared_ptr<StmtNode>> outerElseStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerThenStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerElseStmtList;

		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, d, one);
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(3, d, expression, "d 1 +");
		innerThenStmtList.push_back(assign);

		std::shared_ptr<IfNode> innerIf = std::make_shared<IfNode>(2, innerPred, innerThenStmtList, innerElseStmtList);
		std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(4, z);
		outerThenStmtList.push_back(innerIf);
		outerThenStmtList.push_back(read);

		std::shared_ptr<IfNode> outerWhile = std::make_shared<IfNode>(1, outerPred, outerThenStmtList, outerElseStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ outerWhile };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedModifies;
		std::unordered_set<std::string> assignModifies{ "d" };
		std::unordered_set<std::string> readModifies{ "z" };
		std::unordered_set<std::string> innerIfModifies{ "d" };
		std::unordered_set<std::string> outerIfModifies{ "d", "z" };
		expectedModifies.push_back(std::make_pair(3, assignModifies));
		expectedModifies.push_back(std::make_pair(2, innerIfModifies));
		expectedModifies.push_back(std::make_pair(4, readModifies));
		expectedModifies.push_back(std::make_pair(1, outerIfModifies));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedModifiesStatement();

		REQUIRE(EntityStager::getStagedModifiesStatement() == expectedModifies);

		EntityStager::clear();
	}
}