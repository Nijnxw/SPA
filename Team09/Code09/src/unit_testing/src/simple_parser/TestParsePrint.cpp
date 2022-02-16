#include "asts/NonContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Print 1.2 - Basic print") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("x"),        		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_2());
}
TEST_CASE ("Print 1.2a - A few print statements") {
	std::vector<Token*> input = {
			new NameToken("procedure"),	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("x"), 				new PunctuatorToken(";"),
			new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(2, std::make_shared<VariableNode>("y"));
	std::vector<std::shared_ptr<StmtNode>> stmtLst {printNode1, printNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst {procedureNode};
	AST expected = std::make_shared<ProgramNode>(procLst);

	REQUIRE(*output == *expected);
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid print statement") {
	SECTION("Misspell `print` keyword") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("preen"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '=' but got 'p' instead.\n");
	}
	SECTION ("'print' keyword is case sensitive") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("Print"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '=' but got 'p' instead.\n");
	}
	SECTION ("Constants as var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new IntegerToken("123"),     new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got '123' instead.\n");
	}
	SECTION ("Missing var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got ';' instead.\n");
	}
	SECTION ("Missing ';'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("print"),
				new NameToken("p"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '}' instead.\n");
	}
}
