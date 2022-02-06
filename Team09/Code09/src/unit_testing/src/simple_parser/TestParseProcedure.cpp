#include "simple_parser/Parser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of valid procedure") {
	SECTION("One statement") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	read p;
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("p"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(readNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
	SECTION("A few statements") {
		/*
		 * Test Simple Program
		 * procedure testProgram {
		 * 1	read p;
		 * 2	read testProgram;
		 * }
		 */
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"), 			new PunctuatorToken(";"),
				new NameToken("read"),		new NameToken("testProgram"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};

		Parser parser = Parser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("p"));
		std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("testProgram"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(readNode1), move(readNode2)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::vector<std::shared_ptr<ProcedureNode>> procLst{move(procedureNode)};
		AST expected = std::make_shared<ProgramNode>(procLst);

		REQUIRE(*output == *expected);
	}
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Test parsing of invalid procedure") {
	SECTION ("No statement in stmtLst") {
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
	}
	SECTION ("Misspell `procedure`") {
		std::vector<Token*> input = {
				new NameToken("procedur"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'procedure' but got 'procedur' instead.\n");
	}
	SECTION ("'procedure' keyword is case sensitive") {
		std::vector<Token*> input = {
				new NameToken("Procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'procedure' but got 'Procedure' instead.\n");
	}
	SECTION ("Constants as proc_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new IntegerToken("123"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '123' instead.\n");
	}
	SECTION ("Missing proc_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '{' instead.\n");
	}
	SECTION ("Missing '{'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
												new NameToken("read"),
				new NameToken("p"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '{' but got 'read' instead.\n");
	}
	SECTION ("Missing '}'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("read"),
				new NameToken("p"),			new PunctuatorToken(";"),
												new EndOfFileToken(),
		};
		Parser parser = Parser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement! Expected '}' / 'read' / 'print' but got '' instead.\n");
	}
}