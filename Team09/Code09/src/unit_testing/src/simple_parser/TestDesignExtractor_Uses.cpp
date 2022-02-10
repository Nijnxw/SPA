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

TEST_CASE("Uses - Print Statement") {
	EntityStager::clear();

	/*
	 * Test Simple Program
	 * procedure testProgram {
	 * 1	print x;
	 * }
	 */

	 // building AST
	std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");

	std::shared_ptr<PrintNode> stmt = std::make_shared<PrintNode>(1, x);

	std::vector<std::shared_ptr<StmtNode>> stmtList;
	stmtList.push_back(stmt);

	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procList;
	procList.push_back(proc);

	AST ast = std::make_shared<ProgramNode>(procList);

	DesignExtractor::extractDesignElements(ast);
	
	std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
	std::unordered_set<std::string> vars;
	vars.insert("x");
	expectedUses.push_back(std::make_pair(1, vars));

	REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

	EntityStager::clear();
}

TEST_CASE("Uses - Assign Statement") {
	SECTION("No variable on RHS") {
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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	SECTION("Single variable on RHS") {
		EntityStager::clear();
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = y + 1;
		 * }
		 */

		 // building AST
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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> vars{ "y" };
		expectedUses.push_back(std::make_pair(1, vars));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	SECTION("Multiple variable on RHS") {
		EntityStager::clear();
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	x = x + y;
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");

		ExprNode y = std::make_shared<VariableNode>("y");
		ExprNode expression = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS, x, y);

		std::shared_ptr<AssignNode> stmt = std::make_shared<AssignNode>(1, x, expression, "x y +");

		std::vector<std::shared_ptr<StmtNode>> stmtList;
		stmtList.push_back(stmt);

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> vars{ "x", "y" };
		expectedUses.push_back(std::make_pair(1, vars));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}
}

TEST_CASE("Uses - While Statement") {
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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> vars{ "y" };
		expectedUses.push_back(std::make_pair(1, vars));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	SECTION("Single While loop - simple predicate - print statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2        print x;
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> rel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> pred = std::make_shared<PredicateNode>(rel);

		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(2, x);
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{ print };

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> whileUses{ "y", "x" };
		std::unordered_set<std::string> printUses{ "x" };
		expectedUses.push_back(std::make_pair(2, printUses));
		expectedUses.push_back(std::make_pair(1, whileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	SECTION("Single While loop - simple predicate - assign statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2    	x = x + 1;
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
		std::shared_ptr<AssignNode> assign = std::make_shared<AssignNode>(2, x, expression, "x 1 +");
		std::vector<std::shared_ptr<StmtNode>> whileStmtList{ assign };

		std::shared_ptr<WhileNode> whiles = std::make_shared<WhileNode>(1, pred, whileStmtList);

		std::vector<std::shared_ptr<StmtNode>> stmtList{ whiles };
		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> whileUses{ "y", "x" };
		std::unordered_set<std::string> assignUses{ "x" };
		expectedUses.push_back(std::make_pair(2, assignUses));
		expectedUses.push_back(std::make_pair(1, whileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> whileUses{ "y","z","a","c","d" };
		std::unordered_set<std::string> assignUses{ "d" };
		std::unordered_set<std::string> printUses { "c" };
		expectedUses.push_back(std::make_pair(2, assignUses));
		expectedUses.push_back(std::make_pair(3, printUses));
		expectedUses.push_back(std::make_pair(1, whileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	SECTION("Double Nested While loop - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	while (y > 1) {
		 * 2        while (x > 1) {
		 *          }
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);
		std::shared_ptr<RelExprNode> innerRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> innerPred = std::make_shared<PredicateNode>(innerRel);

		std::vector<std::shared_ptr<StmtNode>> outerWhileStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerWhileStmtList;

		std::shared_ptr<WhileNode> innerWhile = std::make_shared<WhileNode>(2, innerPred, innerWhileStmtList);
		outerWhileStmtList.push_back(innerWhile);

		std::shared_ptr<WhileNode> outerWhile = std::make_shared<WhileNode>(1, outerPred, outerWhileStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ outerWhile };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> innerWhileUses{ "x" };
		std::unordered_set<std::string> outerWhileUses{ "x", "y" };
		expectedUses.push_back(std::make_pair(2, innerWhileUses));
		expectedUses.push_back(std::make_pair(1, outerWhileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

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
		 * 4        print z;
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
		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(4, z);
		outerWhileStmtList.push_back(innerWhile);
		outerWhileStmtList.push_back(print);

		std::shared_ptr<WhileNode> outerWhile = std::make_shared<WhileNode>(1, outerPred, outerWhileStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ outerWhile };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> assignUses{ "d" };
		std::unordered_set<std::string> printUses{ "z" };
		std::unordered_set<std::string> innerWhileUses{ "x", "d"};
		std::unordered_set<std::string> outerWhileUses{ "x", "y", "d", "z"};
		expectedUses.push_back(std::make_pair(3, assignUses));
		expectedUses.push_back(std::make_pair(2, innerWhileUses));
		expectedUses.push_back(std::make_pair(4, printUses));
		expectedUses.push_back(std::make_pair(1, outerWhileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}
}

TEST_CASE("Uses - If Statement") {
	EntityStager::clear();

	SECTION("Single If - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {} else {}
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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> uses{ "y" };
		expectedUses.push_back(std::pair(1, uses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> innerAssign{ "z" };
		std::unordered_set<std::string> outerAssign{ "x" };
		std::unordered_set<std::string> ifUses{ "y", "z"};
		expectedUses.push_back(std::pair(2, innerAssign));
		expectedUses.push_back(std::pair(1, ifUses));
		expectedUses.push_back(std::pair(3, outerAssign));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}

	//todo: everything in between
	SECTION("Single if - complex predicate - multiple lines") {
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

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> ifUses{ "y","z","a","c","d" };
		std::unordered_set<std::string> assignUses{ "d" };
		std::unordered_set<std::string> printUses{ "c" };
		expectedUses.push_back(std::make_pair(2, assignUses));
		expectedUses.push_back(std::make_pair(3, printUses));
		expectedUses.push_back(std::make_pair(1, ifUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();

	}

	SECTION("Double Nested if - simple predicate") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	if (y > 1) then {
		 * 2        if (x > 1) then {} else {}
		 *      } else {
		 * 3        if (z > 1) then {} else {}
		 *      }
		 * }
		 */

		 // building AST
		std::shared_ptr<VariableNode> x = std::make_shared<VariableNode>("x");
		std::shared_ptr<VariableNode> y = std::make_shared<VariableNode>("y");
		std::shared_ptr<VariableNode> z = std::make_shared<VariableNode>("z");
		std::shared_ptr<ConstantNode> one = std::make_shared<ConstantNode>("1");

		std::shared_ptr<RelExprNode> outerRel = std::make_shared<RelExprNode>(y, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> outerPred = std::make_shared<PredicateNode>(outerRel);

		std::shared_ptr<RelExprNode> innerThenRel = std::make_shared<RelExprNode>(x, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> innerThenPred = std::make_shared<PredicateNode>(innerThenRel);
		std::shared_ptr<RelExprNode> innerElseRel = std::make_shared<RelExprNode>(z, ComparatorOperator::GT, one);
		std::shared_ptr<PredicateNode> innerElsePred = std::make_shared<PredicateNode>(innerElseRel);

		std::vector<std::shared_ptr<StmtNode>> outerThenStmtList;
		std::vector<std::shared_ptr<StmtNode>> outerElseStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerThenThenStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerThenElseStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerElseThenStmtList;
		std::vector<std::shared_ptr<StmtNode>> innerElseElseStmtList;

		std::shared_ptr<IfNode> innerThenIf = std::make_shared<IfNode>(2, innerThenPred, innerThenThenStmtList, innerThenElseStmtList);
		outerThenStmtList.push_back(innerThenIf);

		std::shared_ptr<IfNode> innerElseIf = std::make_shared<IfNode>(3, innerElsePred, innerElseThenStmtList, innerElseElseStmtList);
		outerElseStmtList.push_back(innerElseIf);

		std::shared_ptr<IfNode> ifs = std::make_shared<IfNode>(1, outerPred, outerThenStmtList, outerElseStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ ifs };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> innerThenIfUses{ "x" };
		std::unordered_set<std::string> innerThenElseUses{ "z" };
		std::unordered_set<std::string> outerIfUses{ "x", "y", "z"};
		expectedUses.push_back(std::make_pair(2, innerThenIfUses));
		expectedUses.push_back(std::make_pair(3, innerThenElseUses));
		expectedUses.push_back(std::make_pair(1, outerIfUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

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
		 * 4        print z;
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
		std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(4, z);
		outerThenStmtList.push_back(innerIf);
		outerThenStmtList.push_back(print);

		std::shared_ptr<IfNode> outerWhile = std::make_shared<IfNode>(1, outerPred, outerThenStmtList, outerElseStmtList);
		std::vector<std::shared_ptr<StmtNode>> stmtList{ outerWhile };

		std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmtList, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procList;
		procList.push_back(proc);

		AST ast = std::make_shared<ProgramNode>(procList);

		DesignExtractor::extractDesignElements(ast);

		std::vector<std::pair<int, std::unordered_set<std::string>>> expectedUses;
		std::unordered_set<std::string> assignUses{ "d" };
		std::unordered_set<std::string> printUses{ "z" };
		std::unordered_set<std::string> innerWhileUses{ "x", "d" };
		std::unordered_set<std::string> outerWhileUses{ "x", "y", "d", "z" };
		expectedUses.push_back(std::make_pair(3, assignUses));
		expectedUses.push_back(std::make_pair(2, innerWhileUses));
		expectedUses.push_back(std::make_pair(4, printUses));
		expectedUses.push_back(std::make_pair(1, outerWhileUses));

		std::vector<std::pair<int, std::unordered_set<std::string>>> test = EntityStager::getStagedUsesStatement();

		REQUIRE(EntityStager::getStagedUsesStatement() == expectedUses);

		EntityStager::clear();
	}
}