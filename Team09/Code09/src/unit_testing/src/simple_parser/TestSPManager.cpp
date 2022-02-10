#include "catch.hpp"
#include "simple_parser/SPManager.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/AssignNode.h"
#include "pkb/PKB.h"

#include <vector>
#include <unordered_set>

TEST_CASE("Parse SIMPLE file into AST") {
	SECTION("Read file") {
		AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_read.txt");

		std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{readNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}

	SECTION("Print file") {
		AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_print.txt");

		std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}

	SECTION("Assign file") {
		AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_assign.txt");

		std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(1,
																			   std::make_shared<VariableNode>("x"),
																			   std::make_shared<ConstantNode>("3"),
																			   "3");

		ExprNode exprNode2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE,
																  std::make_shared<ConstantNode>("1"),
																  std::make_shared<VariableNode>("x"));
		ExprNode exprNode3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS,
																  std::make_shared<VariableNode>("x"),
																  exprNode2);
		ExprNode exprNode4 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS,
																  exprNode3,
																  std::make_shared<ConstantNode>("2"));
		std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(2,
																			   std::make_shared<VariableNode>("x"),
																			   exprNode4,
																			   "x 1 x / + 2 -");

		std::vector<std::shared_ptr<StmtNode>> stmtLst{assignNode1, assignNode2};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}

	SECTION("Simple source file") {
		AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_SIMPLE.txt");

		std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
		std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
		std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(3, std::make_shared<VariableNode>("y"));
		std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(4, std::make_shared<VariableNode>("x"));

		std::shared_ptr<AssignNode> assignNode1 = std::make_shared<AssignNode>(5,
																			   std::make_shared<VariableNode>("x"),
																			   std::make_shared<ConstantNode>("3"),
																			   "3");

		ExprNode exprNode2 = std::make_shared<BinaryOperatorNode>(BinaryOperator::DIVIDE,
																  std::make_shared<ConstantNode>("1"),
																  std::make_shared<VariableNode>("x"));
		ExprNode exprNode3 = std::make_shared<BinaryOperatorNode>(BinaryOperator::PLUS,
																  std::make_shared<VariableNode>("x"),
																  exprNode2);
		ExprNode exprNode4 = std::make_shared<BinaryOperatorNode>(BinaryOperator::MINUS,
																  exprNode3,
																  std::make_shared<ConstantNode>("2"));
		std::shared_ptr<AssignNode> assignNode2 = std::make_shared<AssignNode>(6,
																			   std::make_shared<VariableNode>("y"),
																			   exprNode4,
																			   "x 1 x / + 2 -");

		std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode1, readNode1, printNode2, readNode2, assignNode1, assignNode2};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE("File do not exist") {
	std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_file";
	REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "File do not exist!\n");
}

TEST_CASE("Invalid SIMPLE syntax") {
	SECTION("Invalid symbols") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_symbols.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Invalid SIMPLE Syntax.\n");
	}
	SECTION("Invalid procedure name") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_procedure_name.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Expected a valid procedure name but got '2' instead.\n");
	}
	SECTION("Invalid variable name") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_variable_name.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Expected a variable name but got '3' instead.\n");
	}
	SECTION("No procedure") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_procedure.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "There must be at least 1 procedure in a SIMPLE program!\n");
	}
	SECTION("No statements") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_no_stmts.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "There must be at least 1 statement in a statement list!\n");
	}
	SECTION("Missing semicolon") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_no_semicolon.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Expected ';' but got '}' instead.\n");
	}
	SECTION("Missing curly braces") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_no_curly_braces.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Expected '{' but got 'read' instead.\n");
	}
}

// Basic test for SPManager::designExtractor()
// Comprehensive test in TestDesignExtractor.cpp
TEST_CASE("Extract design from SIMPLE program") {
	std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
	std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(3, std::make_shared<VariableNode>("y"));
	std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(4, std::make_shared<VariableNode>("x"));

	std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode1, readNode1, printNode2, readNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
	AST ast = std::make_shared<ProgramNode>(procLst);

	SPManager::extractDesign(ast);

	std::unordered_set<std::string> expectedProcedures;
	expectedProcedures.insert("testProgram");
	REQUIRE(PKB::getProcedures() == expectedProcedures);

	std::unordered_set<std::string> expectedVariables;
	std::vector<std::string> vars{"x","y"};
	expectedVariables.insert(vars.begin(), vars.end());
	REQUIRE(PKB::getVariables() == expectedVariables);

	std::unordered_set<int> expectedStmt;
	std::vector<int> stmtNos{1,2,3,4};
	expectedStmt.insert(stmtNos.begin(), stmtNos.end());
	REQUIRE(PKB::getStatementNumbers() == expectedStmt);

	std::unordered_set<int> expectedReadStmt;
	std::vector<int> readStmtNos{2,4};
	expectedReadStmt.insert(readStmtNos.begin(), readStmtNos.end());
	REQUIRE(PKB::getStatementsWithType(EntityType::READ) == expectedReadStmt);

	std::unordered_set<int> expectedPrintStmt;
	std::vector<int> printStmtNos{1,3};
	expectedPrintStmt.insert(printStmtNos.begin(), printStmtNos.end());
	REQUIRE(PKB::getStatementsWithType(EntityType::PRINT) == expectedPrintStmt);

	REQUIRE(PKB::isFollowsRelationship(1, 2));
	REQUIRE(PKB::isFollowsRelationship(3, 4));
	REQUIRE(!PKB::isFollowsRelationship(1, 4));
	REQUIRE(PKB::isFollowsTRelationship(1, 2));
	REQUIRE(PKB::isFollowsTRelationship(1, 4));

	PKB::clearAllStores();
}
