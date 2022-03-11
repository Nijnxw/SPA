#include "catch.hpp"
#include "simple_parser/SPManager.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/AssignNode.h"
#include "pkb/PKB.h"

#include <vector>
#include <unordered_set>
#include <fstream>

const char* tempFile = "./filename.txt";

void createTempFile(std::string program) {
	std::ofstream inputFile(tempFile);
	inputFile << program;
	inputFile.close();
}

void deleteTempFile() {
	remove(tempFile);
}

TEST_CASE("Parse SIMPLE file into AST") {
	SECTION("Read file") {
		std::string program = "procedure testProgram {\n"
							  "    read x;\n"
							  "}";
		createTempFile(program);

		AST output = SPManager::parseFile(tempFile);

		deleteTempFile();

		std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{readNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
		AST expected = std::make_shared<ProgramNode>(procMap);

		REQUIRE(*output == *expected);
	}

	SECTION("Print file") {
		std::string program = "procedure testProgram {\n"
							  "    print x;\n"
							  "}";
		createTempFile(program);

		AST output = SPManager::parseFile(tempFile);

		deleteTempFile();

		std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
		AST expected = std::make_shared<ProgramNode>(procMap);

		REQUIRE(*output == *expected);
	}

	SECTION("Assign file") {
		std::string program = "procedure testProgram {\n"
							  "    x = 3;\n"
							  "    x = x + 1 / x - 2;\n"
							  "}";
		createTempFile(program);

		AST output = SPManager::parseFile(tempFile);

		deleteTempFile();

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
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
		AST expected = std::make_shared<ProgramNode>(procMap);

		REQUIRE(*output == *expected);
	}

	SECTION("Simple source file") {
		std::string program = "procedure testProgram {\n"
							  "    print x;\n"
							  "    read y;\n"
							  "    print y;\n"
							  "    read x;\n"
							  "    x = 3;\n"
							  "    y = x + 1 / x - 2;\n"
							  "}";
		createTempFile(program);

		AST output = SPManager::parseFile(tempFile);

		deleteTempFile();

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

		std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode1, readNode1, printNode2, readNode2, assignNode1,
													   assignNode2};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
		AST expected = std::make_shared<ProgramNode>(procMap);

		REQUIRE(*output == *expected);
	}
}

// Basic test for SPManager::designExtractor()
// Comprehensive test in TestDesignExtractor.cpp
TEST_CASE("Extract design from SIMPLE program") {
	PKB::clearAllStores();
	std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
	std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(3, std::make_shared<VariableNode>("y"));
	std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(4, std::make_shared<VariableNode>("x"));

	std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode1, readNode1, printNode2, readNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
	AST ast = std::make_shared<ProgramNode>(procMap);

	SPManager::stmtCount = 4;
	SPManager::extractDesign(ast);

	std::unordered_set<std::string> expectedProcedures;
	expectedProcedures.insert("testProgram");
	REQUIRE(PKB::getProcedures() == expectedProcedures);

	std::unordered_set<std::string> expectedVariables;
	std::vector<std::string> vars{"x", "y"};
	expectedVariables.insert(vars.begin(), vars.end());
	REQUIRE(PKB::getVariables() == expectedVariables);

	std::unordered_set<int> expectedStmt;
	std::vector<int> stmtNos{1, 2, 3, 4};
	expectedStmt.insert(stmtNos.begin(), stmtNos.end());
	REQUIRE(PKB::getStatementNumbers() == expectedStmt);

	std::unordered_set<int> expectedReadStmt;
	std::vector<int> readStmtNos{2, 4};
	expectedReadStmt.insert(readStmtNos.begin(), readStmtNos.end());
	REQUIRE(PKB::getStatementsWithType(EntityType::READ) == expectedReadStmt);

	std::unordered_set<int> expectedPrintStmt;
	std::vector<int> printStmtNos{1, 3};
	expectedPrintStmt.insert(printStmtNos.begin(), printStmtNos.end());
	REQUIRE(PKB::getStatementsWithType(EntityType::PRINT) == expectedPrintStmt);

	REQUIRE(PKB::isFollowsRelationship(1, 2));
	REQUIRE(PKB::isFollowsRelationship(3, 4));
	REQUIRE(!PKB::isFollowsRelationship(1, 4));
	REQUIRE(PKB::isFollowsTRelationship(1, 2));
	REQUIRE(PKB::isFollowsTRelationship(1, 4));

	PKB::clearAllStores();
}
