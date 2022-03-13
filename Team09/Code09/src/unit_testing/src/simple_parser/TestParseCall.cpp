#include "asts/ContainerStmtASTs.h"
#include "asts/RelationshipASTs.h"
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
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("testProgram2"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new TerminalToken("{"),
			new NameToken("print"),			new NameToken("x"),							new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_79());
}

TEST_CASE ("Call 1.80 - Test call statement (second procedure)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("testProgram"), 		new TerminalToken("{"),
			new NameToken("print"),			new NameToken("x"),							new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("testProgram2"), 	new TerminalToken("{"),
			new NameToken("call"),				new NameToken("testProgram"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_80());
}

TEST_CASE ("Call 1.81 - Call nested in If (first procedure)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("call"), new NameToken("testProgram2"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"),
			new NameToken("procedure"), new NameToken("testProgram2"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_81());
}

TEST_CASE ("Call 1.82 - Call nested in If (second procedure)") {

	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), new NameToken("testProgram2"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("call"), new NameToken("testProgram"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	AST expected = ContainerStmtASTs::getAST1_82();

	REQUIRE(*output == *expected);
}

TEST_CASE ("Call 1.83 - Call nested in While") {
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"), new TerminalToken("{"),
			new NameToken("while"), new TerminalToken("("),
			new NameToken("x"), new TerminalToken("<"), new IntegerToken("1"),
			new TerminalToken(")"), new TerminalToken("{"),
			new NameToken("call"), new NameToken("testProgram2"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"),
			new NameToken("procedure"), new NameToken("testProgram2"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *ContainerStmtASTs::getAST1_83());
}

// Multiple call statements in various orders (Picked from test cases 3.45 - 3.55)

TEST_CASE("Call 3.45 - Multiple call statements in 1 procedure") {
	/*
	 *  procedure testProgram1 {
	 * 1  read y;
	 * 2  call testProgram2;
	 * 3  read x;
	 * 4  call testProgram3;
	 *  }
	 *
	 *  procedure testProgram2 {
	 * 5  print x;
	 * 6  print y;
	 *  }
	 *
	 *  procedure testProgram3 {
	 * 7  x = y + 1;
	 *  }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram1"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new NameToken("call"), new NameToken("testProgram2"), new TerminalToken(";"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("call"), new NameToken("testProgram3"), new TerminalToken(";"),
			new TerminalToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),

			new NameToken("procedure"), new NameToken("testProgram3"), new TerminalToken("{"),
			new NameToken("x"), new TerminalToken("="), new NameToken("y"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new TerminalToken("}"),

			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *RelationshipASTs::getAST3_45());
}

TEST_CASE("Call 3.51 - Multiple call statements across procedures") {
	/*
	 *   procedure testProgram1 {
	 * 1   call testProgram4;
	 * 2   read y;
	 * 3   call testProgram3;
	 * 4   read x;
	 *   }
	 *
	 *   procedure testProgram2 {
	 * 5   print x;
	 * 6   print y;
	 *   }
	 *
	 *   procedure testProgram3 {
	 * 7   x = y + 1;
	 * 8   call testProgram2;
	 *   }
	 *
	 *   procedure testProgram4 {
	 * 9   if (z < 3) then {
	 * 10     read z;
	 * 11     call testProgram2;
	 *     } else {
	 * 12    print z;
	 *     }
	 *   }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram1"), new TerminalToken("{"),
			new NameToken("call"), new NameToken("testProgram4"), new TerminalToken(";"),
			new NameToken("read"), new NameToken("y"), new TerminalToken(";"),
			new NameToken("call"), new NameToken("testProgram3"), new TerminalToken(";"),
			new NameToken("read"), new NameToken("x"), new TerminalToken(";"),
			new TerminalToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("x"), new TerminalToken(";"),
			new NameToken("print"), new NameToken("y"), new TerminalToken(";"),
			new TerminalToken("}"),

			new NameToken("procedure"), new NameToken("testProgram3"), new TerminalToken("{"),
			new NameToken("x"), new TerminalToken("="), new NameToken("y"),
			new TerminalToken("+"), new IntegerToken("1"), new TerminalToken(";"),
			new NameToken("call"), new NameToken("testProgram2"), new TerminalToken(";"),
			new TerminalToken("}"),

			new NameToken("procedure"), new NameToken("testProgram4"), new TerminalToken("{"),
			new NameToken("if"), new TerminalToken("("),
			new NameToken("z"), new TerminalToken("<"), new IntegerToken("3"),
			new TerminalToken(")"), new NameToken("then"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("z"), new TerminalToken(";"),
			new NameToken("call"), new NameToken("testProgram2"), new TerminalToken(";"),
			new TerminalToken("}"), new NameToken("else"), new TerminalToken("{"),
			new NameToken("print"), new NameToken("z"), new TerminalToken(";"),
			new TerminalToken("}"), new TerminalToken("}"),

			new EndOfFileToken(),
	};

	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	REQUIRE(*output == *RelationshipASTs::getAST3_51());
}



// --------------------------------------------------
//                 UNHAPPY PATHS
// --------------------------------------------------

TEST_CASE("'call' keyword is case sensitive") {
	SECTION("Call 10.19 - 'Call'") {
		std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("Call"),			new NameToken("main1"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("main1"), 	new TerminalToken("{"),
			new NameToken("read"),			new NameToken("x"),			new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
	SECTION("Call 10.20 - 'Call'") {
		std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("CALL"),			new NameToken("main1"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("main1"), 	new TerminalToken("{"),
			new NameToken("read"),			new NameToken("x"),			new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 1.\n");
	}
}


TEST_CASE ("Call 11.1 - A procedure cannot call a non-existing procedure") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "A procedure cannot call a non-existing procedure.\n");
}

TEST_CASE ("Call 11.2 - A procedure cannot call itself") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(),
											"Recursive calls are not allowed. Procedure 'main' tried to call itself.\n");
}

TEST_CASE ("Call 11.3 - Cyclic calls are not allowed (2 procedures)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main1"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main2"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("main2"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Cyclic calls are not allowed.\n");
}

TEST_CASE ("Call 11.4 - Cyclic calls are not allowed (3 procedures)") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main1"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main2"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("main2"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main3"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new NameToken("procedure"), 	new NameToken("main3"), 		new TerminalToken("{"),
			new NameToken("call"),				new NameToken("main1"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Cyclic calls are not allowed.\n");
}

TEST_CASE ("Call 11.5 - Invalid proc_name") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("call"),				new IntegerToken("123"),		new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '123' instead.\n");
}

TEST_CASE ("Call 11.6 - Missing proc_name") {
	std::vector<Token*> input = {
			new NameToken("procedure"), 	new NameToken("main"), 		new TerminalToken("{"),
			new NameToken("call"),				new TerminalToken(";"),
			new TerminalToken("}"),
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got ';' instead.\n");
}