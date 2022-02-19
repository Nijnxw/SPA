#include "asts/ContainerStmtASTs.h"
#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Predicate 1.39 - Basic Predicate - Constant to constant comparison") {
	// 1 = 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("=="),		new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_39());
}

TEST_CASE ("Predicate 1.40 - Basic Predicate - Variable to variable comparison") {
	// x < y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),		new OperatorToken("<"),		new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_40());
}

TEST_CASE ("Predicate 1.41 - Basic Predicate - Variable to constant comparison") {
	// x < 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),		new OperatorToken("<"),		new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_41());
}

TEST_CASE ("Predicate 1.42 - Basic Predicate - Test ComparatorOperator::LT") {
	// x < y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),		new OperatorToken("<"),		new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_42());
}

TEST_CASE ("Predicate 1.43 - Basic Predicate - Test ComparatorOperator::LTE") {
	// x <= y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<="),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_43());
}

TEST_CASE ("Predicate 1.44 - Basic Predicate - Test ComparatorOperator::GT") {
	// x > y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken(">"),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_44());
}

TEST_CASE ("Predicate 1.45 - Basic Predicate - Test ComparatorOperator::GTE") {
	// x >= y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken(">="),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_45());
}

TEST_CASE ("Predicate 1.46 - Basic Predicate - Test ComparatorOperator::EQ") {
	// x == y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("=="),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_46());
}

TEST_CASE ("Predicate 1.47 - Basic Predicate - Test ComparatorOperator::NEQ") {
	// x != y
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("!="),			new NameToken("y"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_47());
}

TEST_CASE ("Predicate 1.48 - Basic Predicate - Test ConditionalOperator::NOT") {
	// !(x < 1)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new OperatorToken("!"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_48());
}

TEST_CASE ("Predicate 1.49 - Basic Predicate - Test ConditionalOperator::AND") {
	// (x < 1) && (y >= 3)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken(">="),			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_49());
}

TEST_CASE ("Predicate 1.50 - Basic Predicate - Test ConditionalOperator::OR") {
	// (x < 1) || (y >= 3)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken(">="),			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_50());
}

TEST_CASE ("Predicate 1.51 - Term-Expr Interaction - Term to term comparison") {
	// 1 = 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("=="),		new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_51());
}

TEST_CASE ("Predicate 1.52 - Term-Expr Interaction - Term to expr comparison") {
	// 1 > x + 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken(">"),
			new NameToken("x"),			new OperatorToken("+"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_52());
}

TEST_CASE ("Predicate 1.53 - Term-Expr Interaction - Expr to term comparison") {
	// x + 1 >= 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"), 			new OperatorToken("+"), 			new IntegerToken("1"),
			new OperatorToken(">="),		new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_53());
}

TEST_CASE ("Predicate 1.54 - Term-Expr Interaction - Expr to expr comparison") {
	// x + 1 < y - 2
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),			new IntegerToken("1"),
			new OperatorToken("<"),
			new NameToken("y"), 			new OperatorToken("-"),			new IntegerToken("2"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_54());
}

TEST_CASE ("Predicate 1.55 - Advanced - NOT-OR-AND") {
	// (y + 1 < x) && (!(x == 2) || (1 != 1))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
			new OperatorToken("<"),		new NameToken("x"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new PunctuatorToken("("),	new OperatorToken("!"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("=="),			new IntegerToken("2"),
			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("!="),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_55());
}

TEST_CASE ("Predicate 1.56 - Advanced - OR-AND-NOT") {
	// !((y + 1 < x) && ((x == 2) || (1 != 1)))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new OperatorToken("!"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
			new OperatorToken("<"),		new NameToken("x"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("=="),			new IntegerToken("2"),
			new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("!="),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_56());
}

TEST_CASE ("Predicate 1.57 - Advanced - NOT-OR-AND") {
	// (!(y + 1 < x)) && (((x == 2) || (1 != 1)))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new OperatorToken("!"),		new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
			new OperatorToken("<"),		new NameToken("x"),
			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("=="),			new IntegerToken("2"),
			new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("!="),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_57());
}

TEST_CASE ("Predicate 1.58 - Advanced - AND-NOT-OR") {
	// (!((y + 1 < x) && (x == 2))) || (1 != 1)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),
			new OperatorToken("!"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("+"),			new IntegerToken("1"),
			new OperatorToken("<"),		new NameToken("x"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("=="),			new IntegerToken("2"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new OperatorToken("||"),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("!="),			new IntegerToken("1"),
			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_58());
}

TEST_CASE ("Predicate 9.1 - Parentheses") {
	// (x) < (1)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new NameToken("x"),				new PunctuatorToken(")"),
			new OperatorToken("<"),
			new PunctuatorToken("("),	new IntegerToken("1"),			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_41());
}

TEST_CASE ("Predicate 9.2 - Parentheses") {
	// (((x))) < (((1)))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new OperatorToken("<"),
			new PunctuatorToken("("),	new PunctuatorToken("("),		new PunctuatorToken("("),
			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_41());
}

TEST_CASE ("Predicate 9.3 - Parentheses") {
	// 1 > (((x + 1)))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new IntegerToken("1"),
			new OperatorToken(">"),
			new PunctuatorToken("("),	new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_52());
}

TEST_CASE ("Predicate 9.4 - Parentheses") {
	// (((x + 1))) >= 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken(")"),
			new OperatorToken(">="),
			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_53());
}

TEST_CASE ("Predicate 9.5 - Parentheses") {
	// !((x) < (1))
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new OperatorToken("!"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new PunctuatorToken(")"),		new OperatorToken("<"),
			new PunctuatorToken("("),	new IntegerToken("1"),			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_48());
}

TEST_CASE ("Predicate 9.6 - Parentheses") {
	// ((x) < 1) && ((y) >= 3)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new NameToken("x"),				new PunctuatorToken(")"),
			new OperatorToken("<"),		new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new PunctuatorToken("("),	new NameToken("y"),				new PunctuatorToken(")"),
			new OperatorToken(">="),		new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_49());
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE ("Predicate 9.18 - Constants not a rel_expr") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.19 - Variables not a rel_expr") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.20 - Expr not a rel_expr") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("+"), 			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.21 - rel_expr cannot be wrapped in any parentheses") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got '<' instead.\n");
}

TEST_CASE ("Predicate 9.22 - rel_expr cannot be wrapped in any parentheses") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new PunctuatorToken("("),	new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got '<' instead.\n");
}

TEST_CASE ("Predicate 9.23 - Missing LHS of rel_expr") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
											new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got '<' instead.\n");
}

TEST_CASE ("Predicate 9.24 - Missing RHS of rel_expr") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.25 - Invalid comparator operator") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"), 			new OperatorToken("<="),			new OperatorToken("="),
			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got '=' instead.\n");
}

TEST_CASE ("Predicate 9.26 - Missing parentheses for cond_expr - ConditionalOperator::NOT") {
	// !x < 1
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new OperatorToken("!"),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'x' instead.\n");
}

TEST_CASE ("Predicate 9.27 - Missing parentheses for cond_expr") {
	// x < 1 && (y >= 3)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
											new OperatorToken("&&"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken(">="),			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected arithmetic operator but got '&&' instead.\n");
}

TEST_CASE ("Predicate 9.28 - Missing parentheses for cond_expr") {
	// (x < 1) && y >= 3
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),
			new NameToken("y"),			new OperatorToken(">="),			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'y' instead.\n");
}

TEST_CASE ("Predicate 9.29 - Missing cond_expr - ConditionalOperator::NOT") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new OperatorToken("!"),		new PunctuatorToken("("),		new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.30 - Missing RHS for cond_expr") {
	// () && (y >= 3)
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken(">="),			new IntegerToken("3"),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),		new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE ("Predicate 9.31 - Missing LHS for cond_expr") {
	// (x < 1) && ()
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new OperatorToken("&&"),			new PunctuatorToken("("),
			new PunctuatorToken(")"),	new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}