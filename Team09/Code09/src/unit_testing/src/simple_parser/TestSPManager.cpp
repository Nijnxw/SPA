#include "catch.hpp"
#include "models/simple_parser/AST.h"
#include "simple_parser/SPManager.h"
#include "models/simple_parser/IoNodes.h"

#include <vector>

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

	SECTION("Simple source file") {
		AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_SIMPLE.txt");

		std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
		std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
		std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(3, std::make_shared<VariableNode>("y"));
		std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(4, std::make_shared<VariableNode>("x"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{printNode1, readNode1, printNode2, readNode2};
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

TEST_CASE("Invalid syntax") {
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
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Invalid variable name!\n");
	}
	SECTION("No procedure") {
		std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_procedure.txt";
		REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "Expected 'procedure' but got '' instead.\n");
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
