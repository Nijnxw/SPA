#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"
#include "asts/ContainerStmtASTs.h"

#include "catch.hpp"
#include <vector>

std::vector<Token*> generateTokens(std::string procName) {
	return std::vector<Token*> {
			new NameToken("procedure"), 	new NameToken(procName),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};
}

AST generateBasicAST(std::string procName) {
	std::vector<std::shared_ptr<StmtNode>> stmts {
		std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"))
	};
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, procName);
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {procName, proc} };
	return std::make_shared<ProgramNode>(procMap);
}

AST generateASTs(std::string procName1, std::string procName2) {
  std::vector<std::shared_ptr<StmtNode>> stmts1 {
      std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("x"))
  };
  std::vector<std::shared_ptr<StmtNode>> stmts2 {
      std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("x"))
  };
  std::shared_ptr<ProcedureNode> proc1 = std::make_shared<ProcedureNode>(stmts1, procName1);
  std::shared_ptr<ProcedureNode> proc2 = std::make_shared<ProcedureNode>(stmts2, procName2);
  std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap {{procName1, proc1},
                                                                           {procName2, proc2}};
  return std::make_shared<ProgramNode>(procMap);
}

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE("Proc_name validity 5.1 - Lowercase") {
	// procedure main { read x;}
	std::vector<Token*> input = generateTokens("main");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("main"));
}

TEST_CASE("Proc_name validity 5.2 - Uppercase") {
	// procedure MAIN { read x;}
	std::vector<Token*> input = generateTokens("MAIN");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("MAIN"));
}

TEST_CASE("Proc_name validity 5.3 - Mixed casing") {
	// procedure mAiN { read x;}
	std::vector<Token*> input = generateTokens("mAiN");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("mAiN"));
}

TEST_CASE("Proc_name validity 5.4 - Alphanumeric") {
	// procedure main1 { read x;}
	std::vector<Token*> input = generateTokens("main1");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("main1"));
}

TEST_CASE("Proc_name validity 5.5 - procedure as proc_name") {
	// procedure procedure { read x;}
	std::vector<Token*> input = generateTokens("procedure");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("procedure"));
}

TEST_CASE("Proc_name validity 5.6 - SIMPLE keywords as proc_name") {
	// procedure read { read x;}
	std::vector<Token*> input = generateTokens("read");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("read"));
}

TEST_CASE("Proc_name validity 5.7 - proc_name can be as long as possible") {
	// procedure supercalifragilisticexpialidocious { read x;}
	std::vector<Token*> input = generateTokens("supercalifragilisticexpialidocious");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("supercalifragilisticexpialidocious"));
}

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

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<ReadNode> readNode = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("p"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(readNode)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", move(procedureNode)}};
		AST expected = std::make_shared<ProgramNode>(procMap);

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

		SPParser parser = SPParser(input);
		AST output = parser.parseProgram();

		std::shared_ptr<ReadNode> readNode1 = std::make_shared<ReadNode>(1, std::make_shared<VariableNode>("p"));
		std::shared_ptr<ReadNode> readNode2 = std::make_shared<ReadNode>(2, std::make_shared<VariableNode>("testProgram"));
		std::vector<std::shared_ptr<StmtNode>> stmtLst{move(readNode1), move(readNode2)};
		std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>(stmtLst, "testProgram");
		std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"testProgram", move(procedureNode)} };
		AST expected = std::make_shared<ProgramNode>(procMap);

		REQUIRE(*output == *expected);
	}
}

TEST_CASE("Test multiple procedures") {
	// procedure main { read x; } procedure testProgram { read x; }
	std::vector<Token*> input = generateTokens("main");
	std::vector<Token*> input1 = generateTokens("testProgram");
	input.pop_back();
	input.insert(input.end(), input1.begin(), input1.end());
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	AST expected = generateASTs("main", "testProgram");
	REQUIRE(*output == *expected);
}

TEST_CASE("Multiple procedures 1.74 - Read-if") {
	/*
	 * procedure testProgram {
	 * 1    read z;
	 * }
	 *
	 * procedure testProgram2 {
	 * 2	if (x < 1) then {
	 * 3		read x;
	 * 		} else {
	 * 4		if (y < 1) then {
	 * 5			read y;
	 * 			} else {
	 * 6			print y; } } }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("z"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"),	new PunctuatorToken("{"),
			new NameToken("if"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),

			new NameToken("if"),			new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),

			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *ContainerStmtASTs::getAST1_74());
}

TEST_CASE("Multiple procedures 1.75 - Print-while") {
	/*
	 * procedure testProgram {
	 * 1	print z;
	 *  }
	 *
	 * procedure testProgram2 {
	 * 2	while (!((y + 1 < x) && ((x == 2) || (1 != 1)))) {
	 * 3		read x; } }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("z"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),

			new NameToken("procedure"), 	new NameToken("testProgram2"),	new PunctuatorToken("{"),
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
	REQUIRE(*output == *ContainerStmtASTs::getAST1_75());
}

TEST_CASE("Multiple procedures 1.76 - Assignment-print") {
	/*
	 * procedure testProgram {
	 * 1	a = 1 + (x * (y - 2) / (z % 3));
	 * }
	 *
	 * procedure testProgram2 {
	 * 2	print b;
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new IntegerToken("1"),
			new OperatorToken("+"),		new PunctuatorToken("("),		new NameToken("x"),
			new OperatorToken("*"),		new PunctuatorToken("("),		new NameToken("y"),
			new OperatorToken("-"),		new IntegerToken("2"),			new PunctuatorToken(")"),
			new OperatorToken("/"),		new PunctuatorToken("("),		new NameToken("z"),
			new OperatorToken("%"),		new IntegerToken("3"),			new PunctuatorToken(")"),
			new PunctuatorToken(")"),	new PunctuatorToken(";"),		new PunctuatorToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"),	new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("b"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),

	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *ContainerStmtASTs::getAST1_76());
}

TEST_CASE("Multiple procedures 1.77 - While-read") {
	/*
	 * procedure testProgram {
	 * 1	while (x < 1) {
	 * 2		while (y < 1) {
	 * 3        	read y; } } }
	 *
	 * procedure testProgram2 {
	 * 4	read x; }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("while"),		new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new PunctuatorToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	
			
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *ContainerStmtASTs::getAST1_77());
}

TEST_CASE("Multiple procedures 1.78 - If-assign") {
	/*
	 * procedure testProgram {
	 * 1	if (x < 1) then {
	 * 2		read x;
	 * 		} else {
	 * 3		if (y < 1) then {
	 * 4			read y;
	 * 			} else {
	 * 5			print y; } } }
	 *
	 * procedure testProgram2 {
	 * 6	a = (1 + x * 3) % (y);
	 * }
	 */
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("testProgram"),	new PunctuatorToken("{"),
			new NameToken("if"),		new PunctuatorToken("("),
			new NameToken("x"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),

			new NameToken("if"),		new PunctuatorToken("("),
			new NameToken("y"),			new OperatorToken("<"),			new IntegerToken("1"),
			new PunctuatorToken(")"),	new NameToken("then"),			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new NameToken("else"),			new PunctuatorToken("{"),
			new NameToken("print"),		new NameToken("y"),				new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new PunctuatorToken("}"),		new PunctuatorToken("}"),

			new NameToken("procedure"), new NameToken("testProgram2"),	new PunctuatorToken("{"),
			new NameToken("a"),			new OperatorToken("="),			new PunctuatorToken("("),
			new IntegerToken("1"),		new OperatorToken("+"),			new NameToken("x"),
			new OperatorToken("*"),		new IntegerToken("3"),			new PunctuatorToken(")"),
			new OperatorToken("%"),		new PunctuatorToken("("),		new NameToken("y"),
			new PunctuatorToken(")"),
			new PunctuatorToken(";"),	new PunctuatorToken("}"),
			
			new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *ContainerStmtASTs::getAST1_78());
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Proc_name validity 5.8 - proc_name cannot be an integer") {
	// procedure 123 { read x;}
	std::vector<Token*> input {
			new NameToken("procedure"), 	new IntegerToken("123"),	new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '123' instead.\n");
}

TEST_CASE("Proc_name validity 5.9 - proc_name cannot start with a digit") {
	// procedure 1main { read x;}
	std::vector<Token*> input {
			new NameToken("procedure"), 	new IntegerToken("1"),	new NameToken("main"),
			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '1' instead.\n");
}

TEST_CASE("Proc_name validity 5.10 - proc_name cannot have symbols") {
	// procedure m*in { read x;}
	std::vector<Token*> input {
			new NameToken("procedure"), 	new NameToken("m"),		new OperatorToken("*"),
			new NameToken("in"),
			new PunctuatorToken("{"),
			new NameToken("read"),		new NameToken("x"),		new PunctuatorToken(";"),
			new PunctuatorToken("}"),	new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '{' but got '*' instead.\n");
}

TEST_CASE("Proc_name validity 5.12 - proc_name cannot be repeated") {
  // procedure m*in { read x;}
  std::vector<Token*> input {
      new NameToken("procedure"), 	new NameToken("main"),  new PunctuatorToken("{"),
      new NameToken("read"),		    new NameToken("x"),		  new PunctuatorToken(";"),
      new PunctuatorToken("}"),
      new NameToken("procedure"), 	new NameToken("main"),  new PunctuatorToken("{"),
      new NameToken("read"),		    new NameToken("x"),		  new PunctuatorToken(";"),
      new PunctuatorToken("}"),
      new EndOfFileToken(),
  };
  SPParser parser = SPParser(input);
  REQUIRE_THROWS_WITH(parser.parseProgram(), "There are 2 procedures with the same name 'main'.\n");
}

TEST_CASE ("Test parsing of invalid procedure") {
	SECTION ("No statement in stmtLst") {
		std::vector<Token*> input = {
				new NameToken("procedure"),	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new PunctuatorToken("}"),
				new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 statement in a statement list!\n");
	}
	SECTION ("Misspell `procedure`") {
		std::vector<Token*> input = {
				new NameToken("procedur"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'procedure' but got 'procedur' instead.\n");
	}
	SECTION ("'procedure' keyword is case sensitive") {
		std::vector<Token*> input = {
				new NameToken("Procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected 'procedure' but got 'Procedure' instead.\n");
	}
	SECTION ("Constants as proc_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new IntegerToken("123"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '123' instead.\n");
	}
	SECTION ("Missing proc_name") {
		std::vector<Token*> input = {
				new NameToken("procedure"),
				new PunctuatorToken("{"),   	new NameToken("read"),
				new NameToken("p"),        	new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a valid procedure name but got '{' instead.\n");
	}
	SECTION ("Missing '{'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
												new NameToken("read"),
				new NameToken("p"),			new PunctuatorToken(";"),
				new PunctuatorToken("}"),	new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected '{' but got 'read' instead.\n");
	}
	SECTION ("Missing '}'") {
		std::vector<Token*> input = {
				new NameToken("procedure"), 	new NameToken("testProgram"),
				new PunctuatorToken("{"),	new NameToken("read"),
				new NameToken("p"),			new PunctuatorToken(";"),
												new EndOfFileToken(),
		};
		SPParser parser = SPParser(input);
		REQUIRE_THROWS_WITH(parser.parseProgram(), "Invalid statement syntax at statement 2.\n");
	}
}

TEST_CASE("ProgramNode validity - A program need to have at least 1 procedure") {
	// procedure m*in { read x;}
	std::vector<Token*> input{new EndOfFileToken()};
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "There must be at least 1 procedure in a SIMPLE program!\n");
}