#include "simple_parser/SPParser.h"
#include "simple_parser/SPToken.h"

#include "catch.hpp"
#include "asts/ContainerStmtASTs.h"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------

TEST_CASE ("While 1.59 - Single statement - While-Read") {
	/*
	 * 1  while (x < 1) {
	 * 2    read x;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_59());
}

TEST_CASE ("While 1.60 - Single statement - While-Print") {
	/*
	 * 1  while (x < 1) {
	 * 2    print x;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_60());
}

TEST_CASE ("While 1.61 - Single statement - While-Assign") {
	/*
	 * 1  while (x < 1) {
	 * 2    a = x + 1;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("a"), new TerminalToken("="), new NameToken("x"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_61());
}

TEST_CASE ("While 1.62 - Single statement - While-If") {
	/*
	 * 1  while (x < 1) {
	 * 2    if (y < 1) then {
	 * 3      read y;
	 *      } else {
	 * 4      print y; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_62());
}

TEST_CASE ("While 1.63 - Single statement - While-While") {
	/*
	 * 1  while (x < 1) {
	 * 2    while (y < 1) {
	 * 3 	  read y; } }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_63());
}

TEST_CASE ("While 1.64 - All statement types") {
	/*
	 * 1  while (x < 1) {
	 * 2  	read x;
	 * 3	print x;
	 * 4	a = x + 1;
	 * 5    if (y < 1) then {
	 * 6      read y;
	 *      } else {
	 * 7      print y; }
	 * 8	while (y < 1) {
	 * 9	  read y; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("a"), new TerminalToken("="), new NameToken("x"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_64());
}


// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Invalid while stmt - no stmt in stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 *
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("), new NameToken("x"),
			new TerminalToken("<"), new IntegerToken("1"), new TerminalToken(")"),
			new TerminalToken("{"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid while stmt - no predicate") {
	/*
	 * procedure testProgram {
	 * 1	while () {
	 * 2		read x;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("), new TerminalToken(")"),
			new TerminalToken("{"), new NameToken("read"), new NameToken("x"),
			new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE("Invalid while stmt - invalid predicate") {
	SECTION ("Integer as predicate") {
		/*
		 * procedure testProgram {
		 * 1	while (1) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("while"), new TerminalToken("("), new IntegerToken("1"),
				new TerminalToken(")"),
				new TerminalToken("{"), new NameToken("read"), new NameToken("x"),
				new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
	}
	SECTION ("Missing parentheses") {
		/*
		 * procedure testProgram {
		 * 1	while ((x < 1) || x == 3) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("while"), new TerminalToken("("), new TerminalToken("("),
				new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
				new TerminalToken(")"), new TerminalToken("||"), new NameToken("x"),
				new TerminalToken("=="), new IntegerToken("3"), new TerminalToken(")"),
				new TerminalToken("{"), new NameToken("read"), new NameToken("x"),
				new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'x' instead.\n");
	}
	SECTION ("Invalid rel_expr") {
		/*
		 * procedure testProgram {
		 * 1	while ((x < 1)) {
		 * 2		read x;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("while"), new TerminalToken("("), new TerminalToken("("),
				new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
				new TerminalToken(")"), new TerminalToken(")"), new TerminalToken("{"),
				new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got '<' instead.\n");
	}
}