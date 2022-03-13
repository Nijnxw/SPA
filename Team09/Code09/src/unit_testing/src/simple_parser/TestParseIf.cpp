#include "simple_parser/SPParser.h"
#include "simple_parser/SPToken.h"

#include "catch.hpp"
#include "asts/ContainerStmtASTs.h"
#include <vector>

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------

TEST_CASE ("If 1.65 - Single statement - If-Read") {
	/*
	 * 1  if (x < 1) then {
	 * 2    read x;
	 *    } else {
	 * 3    read y;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_65());
}

TEST_CASE ("If 1.66 - Single statement - If-Print") {
	/*
	 * 1  if (x < 1) then {
	 * 2    print x;
	 *    } else {
	 * 3    print y;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_66());
}

TEST_CASE ("If 1.67 - Single statement - If-Assign") {
	/*
	 * 1  if (x < 1) then {
	 * 2    a = x + 1;
	 *    } else {
	 * 3    a = y + 1;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("a"), new TerminalToken("="), new NameToken("x"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("a"), new TerminalToken("="), new NameToken("y"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_67());
}

TEST_CASE ("If 1.68 - Single statement - If-If (then)") {
	/*
	 * 1  if (x < 1) then {
	 * 2    if (y < 1) then {
	 * 3      read y;
	 *      } else {
	 * 4      print y; }
	 *    } else {
	 * 5    print x;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),

			new NameToken("if"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),

			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_68());
}

TEST_CASE ("If 1.69 - Single statement - If-If (else)") {
	/*
	 * 1  if (x < 1) then {
	 * 2    read x;
	 *    } else {
	 * 3    if (x < 1) then {
	 * 4      read y;
	 *    } else {
	 * 5      print y; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),

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

	REQUIRE(*output == *ContainerStmtASTs::getAST1_69());
}

TEST_CASE ("If 1.70 - Single statement - If-While (then)") {
	/*
	 * 1  if (x < 1) then {
	 * 2    while (y < 1) {
	 * 3	  read y; }
	 *    } else {
	 * 4    print y; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),

			new NameToken("while"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),

			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_70());
}

TEST_CASE ("If 1.71 - Single statement - If-While (else)") {
	/*
	 * 1  if (x < 1) then {
	 * 2    read x;
	 *    } else {
	 * 3    while (y < 1) {
	 * 4	  read y; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),

			new NameToken("while"), new TerminalToken("("),
			new NameToken("y"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),

			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_71());
}

TEST_CASE ("If 1.72 - All statement types - If-then block") {
	/*
	 * 1  if (x < 1) then {
	 * 2	read x;
	 * 3	print x;
	 * 4	a = x + 1;
	 * 5    if (y < 1) then {
	 * 6      read y;
	 *      } else {
	 * 7      print y; }
	 * 8	while (z < 1) {
	 * 9	  read z; }
	 *    } else {
	 * 10   print x;
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
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
			new NameToken("z"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("z"), new TerminalToken(";"),
			new TerminalToken("}"),

			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_72());
}

TEST_CASE ("If 1.73 - All statement types - If-else block") {
	/*
	 * 1  if (x < 1) then {
	 * 2    read x;
	 *    } else {
	 * 3	read x;
	 * 4	print x;
	 * 5	a = z + 1;
	 * 6    if (x < 1) then {
	 * 7      read y;
	 *      } else {
	 * 8      print y; }
	 * 9	while (z < 1) {
	 * 10 	  read z; }
	 *    }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
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
			new NameToken("z"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("z"), new TerminalToken(";"),
			new TerminalToken("}"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_73());
}

// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Invalid if stmt - no stmt in then stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 *
	 * 		} else {
	 * 2		print y;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("), new NameToken("x"),
			new TerminalToken("<"), new IntegerToken("1"), new TerminalToken(")"),
			new NameToken("then"), new TerminalToken("{"), new TerminalToken("}"),
			new NameToken("else"), new TerminalToken("{"), new NameToken("print"),
			new NameToken("y"), new TerminalToken("}"), new TerminalToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid if stmt - no stmt in else stmtLst") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		} else {
	 *
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("), new NameToken("x"),
			new TerminalToken("<"), new IntegerToken("1"), new TerminalToken(")"),
			new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
}

TEST_CASE("Invalid if stmt - no predicate") {
	/*
	 * procedure testProgram {
	 * 1	if () then {
	 * 2		read x;
	 * 		} else {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("), new TerminalToken(")"),
			new NameToken("then"), new TerminalToken("{"), new NameToken("read"),
			new NameToken("x"), new TerminalToken(";"), new TerminalToken("}"),
			new NameToken("else"), new TerminalToken("{"), new NameToken("print"),
			new NameToken("y"), new TerminalToken(";"), new TerminalToken("}"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected an expression but got ')' instead.\n");
}

TEST_CASE("Invalid if stmt - invalid predicate") {
	SECTION ("Integer as predicate") {
		/*
		 * procedure testProgram {
		 * 1	if (1) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("if"), new TerminalToken("("), new IntegerToken("1"),
				new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
				new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
				new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
				new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
				new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected comparator operator but got ')' instead.\n");
	}
	SECTION ("Missing parentheses") {
		/*
		 * procedure testProgram {
		 * 1	if x < 1) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("if"),
				new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
				new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
				new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
				new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
				new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
				new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
		};


		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '(' but got 'x' instead.\n");
	}
	SECTION ("Invalid rel_expr") {
		/*
		 * procedure testProgram {
		 * 1	if ((x < 1)) then {
		 * 2		read x;
		 * 		} else {
		 * 3		print y;
		 * 		}
		 * }
		 */
		std::vector<SPToken*> input = {
				new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
				new NameToken("if"), new TerminalToken("("), new TerminalToken("("),
				new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
				new TerminalToken(")"), new TerminalToken(")"), new NameToken("then"),
				new TerminalToken("{"),
				new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
				new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
				new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
				new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
		};

		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ')' but got '<' instead.\n");
	}
}

TEST_CASE("Invalid if stmt - no 'then' keyword") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1)  {
	 * 2 		read x;
	 * 		} else {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'then' but got '{' instead.\n");
}

TEST_CASE("Invalid if stmt - no 'else' keyword") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		}  {
	 * 3		print y;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'else' but got '{' instead.\n");
}

TEST_CASE("Invalid if stmt - no 'else' block") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2 		read x;
	 * 		}
	 * }
	 */
	std::vector<SPToken*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"), new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'else' but got '}' instead.\n");
}