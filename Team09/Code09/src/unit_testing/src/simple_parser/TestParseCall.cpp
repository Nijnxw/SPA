#include "asts/ContainerStmtASTs.h"
#include "simple_parser/Token.h"
#include "simple_parser/SPParser.h"
#include "models/simple_parser/AST.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Call 1.79 - Test call statement (first procedure)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("testProgram2"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("x"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_79());
}

TEST_CASE ("Call 1.80 - Test call statement (second procedure)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("x"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("testProgram"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_80());
}

TEST_CASE ("Call 1.81 - Call nested in If (first procedure)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new PunctuatorToken("{"),
			new NameToken("if"), 				new PunctuatorToken("("),
			new NameToken("x"),					new OperatorToken("<"),					new IntegerToken("1"),
			new PunctuatorToken(")"),		new NameToken("then"),						new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("x"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),		new NameToken("else"),						new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("testProgram2"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),		new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("y"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_81());
}

TEST_CASE ("Call 1.82 - Call nested in If (second procedure)") {

	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("x"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new PunctuatorToken("{"),
			new NameToken("if"), 				new PunctuatorToken("("),
			new NameToken("x"),					new OperatorToken("<"),					new IntegerToken("1"),
			new PunctuatorToken(")"),		new NameToken("then"),						new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("y"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),		new NameToken("else"),						new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("testProgram"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),		new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	AST expected = ContainerStmtASTs::getAST1_82();

	REQUIRE(*output == *expected);
}

TEST_CASE ("Call 1.83 - Call nested in While") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new PunctuatorToken("{"),
			new NameToken("while"), 				new PunctuatorToken("("),
			new NameToken("x"),					new OperatorToken("<"),					new IntegerToken("1"),
			new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("testProgram2"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),		new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new PunctuatorToken("{"),
			new NameToken("print"),			new NameToken("y"),							new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_83());
}

// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Call 11.1 - A procedure cannot call a non-existing procedure") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "A procedure cannot call a non-existing procedure.\n");
}

TEST_CASE ("Call 11.2 - A procedure cannot call itself") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(),
											"Recursive calls are not allowed. Procedure 'main' tried to call itself.\n");
}

TEST_CASE ("Call 11.3 - Cyclic calls are not allowed (2 procedures)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main1"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main2"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("main2"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Cyclic calls are not allowed.\n");
}

TEST_CASE ("Call 11.4 - Cyclic calls are not allowed (3 procedures)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main1"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main2"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("main2"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main3"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new NameToken("procedure"), 	new NameToken("main3"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Cyclic calls are not allowed.\n");
}

TEST_CASE ("Call 11.5 - Invalid proc_name") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new IntegerToken("123"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '123' instead.\n");
}

TEST_CASE ("Call 11.6 - Missing proc_name") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new PunctuatorToken("{"),
			new NameToken("call"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got ';' instead.\n");
}