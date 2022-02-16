#include "asts/NonContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Read 1.1 - Basic read") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),        		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_1());
}

TEST_CASE ("Read 1.1a - A few read statements") {
	std::vector<Token*> input = {
			new NameToken("procedure"),	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"), 				new PunctuatorToken(";"),
			new NameToken("read"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"));
	std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("y"));
	std::vector<std::shared_ptr<StmtNode>> stmtLst {readNode1, readNode2};
	std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
	std::vector<std::shared_ptr<ProcedureNode>> procLst {procedureNode};
	AST expected = std::make_shared<ProgramNode>(procLst);

	REQUIRE(*output == *expected);
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid read statement") {
	SECTION ("Misspell `read` keyword") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("reed"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '=' but got 'p' instead.\n");
	}
	SECTION ("'read' keyword is case sensitive") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("Read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '=' but got 'p' instead.\n");
	}
	SECTION ("Constants as var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new IntegerToken("123"),     new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got '123' instead.\n");
	}
	SECTION ("Missing var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got ';' instead.\n");
	}
	SECTION ("Missing ';'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("read"),
				new NameToken("p"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '}' instead.\n");
	}
}
