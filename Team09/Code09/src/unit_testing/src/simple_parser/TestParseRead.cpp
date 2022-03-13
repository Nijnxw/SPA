#include "asts/NonContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/SPToken.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Read 1.1 - Basic read") {
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_1());
}

TEST_CASE ("Read 1.1a - A few read statements") {
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
	std::vector<std::shared_ptr<StmtNode>> stmtLst {readNode1, readNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", move(procedureNode)} };
	AST expected = std::make_shared<ProgramNode>(procMap);

	REQUIRE(*output == *expected);
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid read statement") {
	SECTION ("Misspell `read` keyword") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("reed"),
				new NameToken("p"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("'read' keyword is case sensitive") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("Read"),
				new NameToken("p"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("Constants as var_name") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("read"),
				new IntegerToken("123"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got '123' instead.\n");
	}
	SECTION ("Missing var_name") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("read"),
				new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got ';' instead.\n");
	}
	SECTION ("Missing ';'") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("read"),
				new NameToken("p"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '}' instead.\n");
	}
}
