#include "simple_parser/Parser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of valid print statements") {
	SECTION("One print statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	print p;
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<PrintNode> printNode = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("p"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(printNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("A few print statements") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	print p;
		 * 2	print testProgram;
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new NameToken("p"), 			new PunctuatorToken(";"),
				new NameToken("print"),		new NameToken("testProgram"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<PrintNode> printNode1 = std::make_shared<PrintNode>(1, std::make_shared<VariableNode>("p"));
		std::shared_ptr<PrintNode> printNode2 = std::make_shared<PrintNode>(2, std::make_shared<VariableNode>("testProgram"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(printNode1), move(printNode2)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
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
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement! Expected '}' / 'read' / 'print' but got 'preen' instead.\n");
	}
	SECTION ("'print' keyword is case sensitive") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("Print"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement! Expected '}' / 'read' / 'print' but got 'Print' instead.\n");
	}
	SECTION ("Constants as var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new IntegerToken("123"),     new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid variable name!\n");
	}
	SECTION ("Missing var_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("print"),
				new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid variable name!\n");
	}
	SECTION ("Missing ';'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("print"),
				new NameToken("p"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '}' instead.\n");
	}
}
