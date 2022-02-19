#include "asts/NonContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Assign 1.3 - Variable-Constant Interaction - Single constant") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_3());
}

TEST_CASE ("Assign 1.4 - Variable-Constant Interaction - Single variable") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_4());

}

TEST_CASE ("Assign 1.5 - Variable-Constant Interaction - Two variables") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_5());
}

TEST_CASE ("Assign 1.6 - Variable-Constant Interaction - Two constants") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new OperatorToken("+"),		new IntegerToken("2"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_6());
}

TEST_CASE ("Assign 1.7 - Variable-Constant Interaction - Variable and constant") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_7());
}

TEST_CASE ("Assign 1.8 - Variable-Constant Interaction - 5 variables and constants") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new OperatorToken("+"),		new NameToken("x"),
			new OperatorToken("+"),		new NameToken("y"),
			new OperatorToken("+"),		new IntegerToken("2"),
			new OperatorToken("+"),		new NameToken("z"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_8());
}

TEST_CASE ("Assign 1.9 - Operator - Addition operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_9());
}

TEST_CASE ("Assign 1.10 - Operator - Subtraction operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("-"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_10());
}

TEST_CASE ("Assign 1.11 - Operator - Multiplication operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("*"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_11());
}

TEST_CASE ("Assign 1.12 - Operator - Division operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("/"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_12());
}

TEST_CASE ("Assign 1.13 - Operator - Modulo operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("%"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_13());
}

TEST_CASE ("Assign 1.14 - Operator Precedence Basic - '+' and '-' same level precedence") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),
			new OperatorToken("-"),		new NameToken("y"),
			new OperatorToken("+"),		new IntegerToken("3"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_14());
}

TEST_CASE ("Assign 1.15 - Operator Precedence Basic - '*', '/' and '%' same level precedence") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("*"),		new IntegerToken("1"),
			new OperatorToken("/"),		new NameToken("y"),
			new OperatorToken("%"),		new IntegerToken("3"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_15());
}

TEST_CASE ("Assign 1.16 - Operator Precedence Basic - '+' and '*' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),
			new OperatorToken("*"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_16());
}

TEST_CASE ("Assign 1.17 - Operator Precedence Basic - '+' and '/' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),
			new OperatorToken("/"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_17());
}

TEST_CASE ("Assign 1.18 - Operator Precedence Basic - '+' and '%' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new IntegerToken("1"),
			new OperatorToken("%"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_18());
}

TEST_CASE ("Assign 1.19 - Operator Precedence Basic - '-' and '*' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("-"),		new IntegerToken("1"),
			new OperatorToken("*"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_19());
}

TEST_CASE ("Assign 1.20 - Operator Precedence Basic - '-' and '/' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("-"),		new IntegerToken("1"),
			new OperatorToken("/"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_20());
}

TEST_CASE ("Assign 1.21 - Operator Precedence Basic - '-' and '%' interaction") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("-"),		new IntegerToken("1"),
			new OperatorToken("%"),		new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_21());
}

TEST_CASE ("Assign 1.22 - Operator Precedence with Parentheses - Single constant") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_22());
}

TEST_CASE ("Assign 1.23 - Operator Precedence with Parentheses - Single variable") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new NameToken("x"),			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_23());
}

TEST_CASE ("Assign 1.24 - Operator Precedence with Parentheses - Single expression") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),				new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_24());
}

TEST_CASE ("Assign 1.25 - Operator Precedence with Parentheses - (x + 1) + y") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),				new IntegerToken("1"),
			new PunctuatorToken(")"),		new OperatorToken("+"),				new NameToken("y"),
			new PunctuatorToken(";"),		new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_25());
}

TEST_CASE ("Assign 1.26 - Operator Precedence with Parentheses - x + (1 + y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new PunctuatorToken("("),	 	new IntegerToken("1"),
			new OperatorToken("+"),		new NameToken("y"),				new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_26());
}

TEST_CASE ("Assign 1.27 - Operator Precedence with Parentheses - x + (1 * y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("+"),		new PunctuatorToken("("),	 	new IntegerToken("1"),
			new OperatorToken("*"),		new NameToken("y"),				new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_27());
}

TEST_CASE ("Assign 1.28 - Operator Precedence with Parentheses - x * (1 + y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("*"),		new PunctuatorToken("("),	 	new IntegerToken("1"),
			new OperatorToken("+"),		new NameToken("y"),				new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_28());
}

TEST_CASE ("Assign 1.29 - Operator Precedence with Parentheses - (x * 1) * y") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("*"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("*"),			new NameToken("y"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_29());
}

TEST_CASE ("Assign 1.30 - Operator Precedence with Parentheses - x * (1 * y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new NameToken("x"),
			new OperatorToken("*"),		new PunctuatorToken("("),	 	new IntegerToken("1"),
			new OperatorToken("*"),		new NameToken("y"),				new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_30());
}

TEST_CASE ("Assign 1.31 - Operator Precedence Intermediate - (1 + (x - y)) / 3") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("-"),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),			new OperatorToken("/"),
			new IntegerToken("3"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_31());
}

TEST_CASE ("Assign 1.32 - Operator Precedence Intermediate - (1 + x) - (y / 3)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"), 			new NameToken("x"),
			new PunctuatorToken(")"),	new OperatorToken("-"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("/"),			new IntegerToken("3"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_32());
}

TEST_CASE ("Assign 1.33 - Operator Precedence Intermediate - (1 + (x) - 3 % y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"), 			new PunctuatorToken("("),
			new NameToken("x"),			new PunctuatorToken(")"),		new OperatorToken("-"),
			new IntegerToken("3"),		new OperatorToken("%"),			new NameToken("y"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_33());
}

TEST_CASE ("Assign 1.34 - Operator Precedence Intermediate - (1 + x * 3) % (y)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"), 			new NameToken("x"),
			new OperatorToken("*"),		new IntegerToken("3"),			new PunctuatorToken(")"),
			new OperatorToken("%"),		new PunctuatorToken("("),		new NameToken("y"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_34());
}

TEST_CASE ("Assign 1.35 - Operator Precedence Intermediate - 1 + (x * (y - 2)) / (z % 3)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new OperatorToken("+"),		new PunctuatorToken("("),		new NameToken("x"),
			new OperatorToken("*"),		new PunctuatorToken("("),		new NameToken("y"),
			new OperatorToken("-"),		new IntegerToken("2"),			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new OperatorToken("/"),			new PunctuatorToken("("),
			new NameToken("z"),			new OperatorToken("%"),			new IntegerToken("3"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_35());
}

TEST_CASE ("Assign 1.36 - Operator Precedence Intermediate - (1 + (x * y)) - (2 / z % 3)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("*"),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new OperatorToken("-"),
			new PunctuatorToken("("),	new IntegerToken("2"),			new OperatorToken("/"),
			new NameToken("z"),			new OperatorToken("%"),			new IntegerToken("3"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_36());
}

TEST_CASE ("Assign 1.37 - Operator Precedence Intermediate - (1 + (x * (y - 2 / z % 3)))") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("*"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("-"),			new IntegerToken("2"),
			new OperatorToken("/"),		new NameToken("z"),				new OperatorToken("%"),
			new IntegerToken("3"),		new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_37());
}

TEST_CASE ("Assign 1.38 - Operator Precedence Intermediate - 1 + (x * (y - 2) / (z % 3))") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new OperatorToken("+"),		new PunctuatorToken("("),		new NameToken("x"),
			new OperatorToken("*"),		new PunctuatorToken("("),		new NameToken("y"),
			new OperatorToken("-"),		new IntegerToken("2"),			new PunctuatorToken(")"),
			new OperatorToken("/"),		new PunctuatorToken("("),			new NameToken("z"),
			new OperatorToken("%"),		new IntegerToken("3"),			new PunctuatorToken(")"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *NonContainerStmtASTs::getAST1_38());
}

TEST_CASE ("Expression validity 8.1") {
	// a = (1);
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),  	new IntegerToken("1"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_3());
}

TEST_CASE ("Expression validity 8.2") {
	// a = (x);
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),		new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),  	new NameToken("x"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_4());
}

TEST_CASE ("Expression validity 8.3") {
	// a = (x + 1);
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),		new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new NameToken("x"),			new OperatorToken("+"),
			new IntegerToken("1"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_7());
}

TEST_CASE ("Expression validity 8.4") {
	// a = (((1)));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),		new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),  	new PunctuatorToken("("),	new PunctuatorToken("("),
			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_3());
}

TEST_CASE ("Expression validity 8.5") {
	// a = (((x)));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),		new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new PunctuatorToken("("),	new PunctuatorToken("("),
			new NameToken("x"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),	new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_4());
}

TEST_CASE ("Expression validity 8.6") {
	// a = (((x + 1)));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new PunctuatorToken("("), 		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),  		new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_7());
}

TEST_CASE ("Expression validity 8.7") {
	// a = (((x) + 1));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new PunctuatorToken("("), 		new PunctuatorToken("("),
			new NameToken("x"),			new PunctuatorToken(")"),
			new OperatorToken("+"),  	new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_7());
}

TEST_CASE ("Expression validity 8.8") {
	// a = (x) + (( (1) + y ));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new NameToken("x"),				new PunctuatorToken(")"),
			new OperatorToken("+"),
			new PunctuatorToken("("),	new PunctuatorToken("("),
			new PunctuatorToken("("),  	new IntegerToken("1"),			new PunctuatorToken(")"),
			new OperatorToken("+"),		new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_26());
}

TEST_CASE ("Expression validity 8.9") {
	// a = ((1 + (x * ((y) - 2)) / (z % 3)));
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),	new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"),
			new PunctuatorToken("("),	new NameToken("x"),				new OperatorToken("*"),
			new PunctuatorToken("("),
			new PunctuatorToken("("),  	new NameToken("y"),				new PunctuatorToken(")"),
			new OperatorToken("-"),		new IntegerToken("2"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new OperatorToken("/"),
			new PunctuatorToken("("),
			new NameToken("z"),	 		new OperatorToken("%"), 			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *NonContainerStmtASTs::getAST1_35());
}


// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Expression validity 8.10 - Missing ‘)’") {
	// a = (x;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),  	new NameToken("x"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got ';' instead.\n");
}

TEST_CASE ("Expression validity 8.11 - Missing ‘(’") {
	// a = x);
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got ')' instead.\n");
}

TEST_CASE ("Expression validity 8.12 - Invalid pairing") {
	// a = )x(;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken(")"),  	new NameToken("x"),				new PunctuatorToken("("),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE ("Expression validity 8.13 - Invalid wrapping of parentheses around expr") {
	// a = (x + ) 1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new PunctuatorToken("("),  	new NameToken("x"),				new OperatorToken("+"),
			new PunctuatorToken(")"),	new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE ("Expression validity 8.14 - Invalid wrapping of parentheses around expr") {
	// a = x ( + 1);
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),			new PunctuatorToken("("),  		new OperatorToken("+"),
			new IntegerToken("1"),		new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '(' instead.\n");
}

TEST_CASE ("Expression validity 8.15 - Invalid wrapping of parentheses around expr") {
	// a = x (+) 1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),			new PunctuatorToken("("),  		new OperatorToken("+"),
			new PunctuatorToken(")"),	new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '(' instead.\n");
}

TEST_CASE ("Expression validity 8.16 - No operator") {
	// a = 1x;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new IntegerToken("1"),		new NameToken("x"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got 'x' instead.\n");
}

TEST_CASE ("Expression validity 8.17 - Invalid operator") {
	// a = x < 1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '<' instead.\n");
}

TEST_CASE ("Expression validity 8.18 - Invalid operator") {
	// a = x && 1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),			new OperatorToken("&&"),			new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '&&' instead.\n");
}

TEST_CASE ("Expression validity 8.19 - Invalid operator") {
	// a = x ! 1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new NameToken("x"),			new OperatorToken("!"),			new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '!' instead.\n");
}

TEST_CASE ("Expression validity 8.20 - Invalid operator") {
	// a = !x;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new OperatorToken("!"),		new NameToken("x"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got '!' instead.\n");
}

TEST_CASE ("Expression validity 8.21 - Negative integers not supported") {
	// a = -1;
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),
			new OperatorToken("-"),		new IntegerToken("1"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got '-' instead.\n");
}

TEST_CASE ("Test parsing of invalid assign statements") {
	SECTION ("Constants as var_name") {
		// 123 = x;
		std::vector<Token *> input = {
				new NameToken("procedure"), new NameToken("testProgram"),
				new PunctuatorToken("{"), new IntegerToken("123"),
				new OperatorToken("="), new NameToken("x"),
				new PunctuatorToken(";"), new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("Missing ';'") {
		// a = x
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
												new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '}' instead.\n");
	}
	SECTION ("Missing lhs") {
		// = x;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),
				new OperatorToken("="),		new NameToken("x"),
				new PunctuatorToken(";"),	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION ("Missing rhs") {
		// a = ;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("a"),
				new OperatorToken("="),		new PunctuatorToken(";"),
				new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ';' instead.\n");
	}
}

TEST_CASE("Invalid expressions") {
	SECTION ("Missing operators") {
		// a = x   b;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
				new NameToken("b"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got 'b' instead.\n");
	}
	SECTION ("Missing operands") {
		// a = x + b /;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
				new OperatorToken("+"),		new NameToken("b"),
				new OperatorToken("/"),		new PunctuatorToken(";"),
				new PunctuatorToken("}"), 	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ';' instead.\n");
	}
	SECTION ("extra operands") {
		// a = x +- b;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
				new OperatorToken("+"),		new OperatorToken("-"),
				new NameToken("b"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got '-' instead.\n");
	}
	SECTION ("Missing opening parentheses") {
		// a = x + b - 1);
		std::vector<Token *> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"), 	new NameToken("a"),
				new OperatorToken("="), 		new NameToken("x"),
				new OperatorToken("+"), 		new NameToken("b"),
				new OperatorToken("-"), 		new IntegerToken("1"),
				new PunctuatorToken(")"), 	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got ')' instead.\n");

		// a = x + (b - 1)) / 3;
		std::vector<Token *> input1 = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"), 	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
				new OperatorToken("+"),		new PunctuatorToken("("),
				new NameToken("b"),			new OperatorToken("-"),
				new IntegerToken("1"),		new PunctuatorToken(")"),
				new PunctuatorToken(")"), 		new OperatorToken("/"),
				new IntegerToken("3"), 		new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser1 = SPParser(input1);
		REQUIRE_THROWS_WITH(parser1.parseProgram(), "Expected ';' but got ')' instead.\n");
	}
	SECTION("Missing closing parentheses") {
		// a = x + (b - 1;
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("a"),
				new OperatorToken("="),		new NameToken("x"),
				new OperatorToken("+"),		new PunctuatorToken("("),
				new NameToken("b"),				new OperatorToken("-"),
				new IntegerToken("1"),		new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '}' instead.\n");

		// a = (x + (b - 1) / 3;
		std::vector<Token *> input1 = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"), 	new NameToken("a"),
				new OperatorToken("="), 		new PunctuatorToken("("),
				new NameToken("x"),			new OperatorToken("+"),
				new PunctuatorToken("("),	new NameToken("b"),
				new OperatorToken("-"), 		new IntegerToken("1"),
				new PunctuatorToken(")"), 	new OperatorToken("/"),
				new IntegerToken("3"), 		new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser1 = SPParser(input1);
		REQUIRE_THROWS_WITH(parser1.parseProgram(), "Expected ')' but got ';' instead.\n");
	}
}

