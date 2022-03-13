#include "asts/NonContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/SPToken.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Print 1.2 - Basic print") {
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_2());
}
TEST_CASE ("Print 1.2a - A few print statements") {
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(2, std::make_shared<VariableNode>("y"));
	std::vector<std::shared_ptr<StmtNode>> stmtLst {printNode1, printNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", procedureNode} };
	AST expected = std::make_shared<ProgramNode>(procMap);

	REQUIRE(*output == *expected);
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid print statement") {
	SECTION("Misspell `print` keyword") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("preen"),
				new NameToken("p"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("'print' keyword is case sensitive") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("Print"),
				new NameToken("p"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("Constants as var_name") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("print"),
				new IntegerToken("123"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got '123' instead.\n");
	}
	SECTION ("Missing var_name") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("print"),
				new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got ';' instead.\n");
	}
	SECTION ("Missing ';'") {
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new TerminalToken("{"), new NameToken("print"),
				new NameToken("p"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '}' instead.\n");
	}
}
