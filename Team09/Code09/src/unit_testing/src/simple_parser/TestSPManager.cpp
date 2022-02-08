#include "catch.hpp"
#include "models/simple_parser/AST.h"
#include "simple_parser/SPManager.h"
#include "models/simple_parser/IoNodes.h"

#include <vector>

TEST_CASE("Parse SIMPLE file into AST") {
	AST output = SPManager::parseFile("../../../src/unit_testing/tests/simple_source/valid_read.txt");

	std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"));
	std::vector<std::shared_ptr<StmtNode>> stmtLst{readNode};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst{procedureNode};
	AST expected = std::make_shared<ProgramNode>(procLst);

	REQUIRE(*output == *expected);
}

TEST_CASE("File do not exist") {
	std::string filename = "../../../src/unit_testing/tests/simple_source/invalid_file";
	REQUIRE_THROWS_WITH(SPManager::parseFile(filename), "File do not exist!\n");
}
