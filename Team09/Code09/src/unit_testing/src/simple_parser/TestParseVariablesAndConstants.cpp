#include "simple_parser/SPParser.h"
#include "simple_parser/Token.h"

#include "catch.hpp"
#include <vector>

std::vector<Token*> generateTokens(std::string varName, bool isReadStmt = true) {
	if (isReadStmt) {
		return std::vector<Token*> {
				new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
				new NameToken("read"), new NameToken(varName), new TerminalToken(";"),
				new TerminalToken("}"), new EndOfFileToken(),
		};
	}
	return std::vector<Token*> {
			new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
			new NameToken(varName), new TerminalToken("="), new IntegerToken("1"),
			new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
	};
}

AST generateBasicAST(std::string varName, bool isReadStmt = true) {
	std::vector<std::shared_ptr<StmtNode>> stmts;
	if (isReadStmt) {
		stmts.push_back(std::make_shared<ReadNode>(1, std::make_shared<VariableNode>(varName)));
	} else {
		stmts.push_back(
				std::make_shared<AssignNode>(1,
											 std::make_shared<VariableNode>(varName),
											 std::make_shared<ConstantNode>("1"),
											 "1")
		);
	}
	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, "main");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"main", proc} };
	return std::make_shared<ProgramNode>(procMap);
}

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------
TEST_CASE("Var_name validity 6.1 - Lowercase") {
	// read main;
	std::vector<Token*> input = generateTokens("main");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("main"));
}

TEST_CASE("Var_name validity 6.2 - Uppercase") {
	// read MAIN;
	std::vector<Token*> input = generateTokens("MAIN");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("MAIN"));
}

TEST_CASE("Var_name validity 6.3 - Mixed case") {
	// read mAiN;
	std::vector<Token*> input = generateTokens("mAiN");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("mAiN"));
}

TEST_CASE("Var_name validity 6.4 - Alphanumeric") {
	// read main1;
	std::vector<Token*> input = generateTokens("main1");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("main1"));
}

TEST_CASE("Var_name validity 6.5 - procedure as var_name") {
	// procedure = 1;
	std::vector<Token*> input = generateTokens("procedure", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("procedure", false));
}

TEST_CASE("Var_name validity 6.6 - read as var_name") {
	// read = 1;
	std::vector<Token*> input = generateTokens("read", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("read", false));
}

TEST_CASE("Var_name validity 6.7 - print as var_name") {
	// print = 1;
	std::vector<Token*> input = generateTokens("print", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("print", false));
}

TEST_CASE("Var_name validity 6.8 - while as var_name") {
	// while = 1;
	std::vector<Token*> input = generateTokens("while", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("while", false));
}

TEST_CASE("Var_name validity 6.9 - if as var_name") {
	// if = 1;
	std::vector<Token*> input = generateTokens("if", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("if", false));
}

TEST_CASE("Var_name validity 6.10 - else as var_name") {
	// else = 1;
	std::vector<Token*> input = generateTokens("else", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("else", false));
}

TEST_CASE("Var_name validity 6.11 - then as var_name") {
	// then = 1;
	std::vector<Token*> input = generateTokens("then", false);
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("then", false));
}

TEST_CASE("Var_name validity 6.12 - var_name can be as long as possible") {
	// read supercalifragilisticexpialidocious;
	std::vector<Token*> input = generateTokens("supercalifragilisticexpialidocious");
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();
	REQUIRE(*output == *generateBasicAST("supercalifragilisticexpialidocious"));
}

TEST_CASE("Const validity 7.1 - constant") {
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
			new NameToken("x"), new TerminalToken("="),
			new IntegerToken("12345"),
			new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::vector<std::shared_ptr<StmtNode>> stmts{
			std::make_shared<AssignNode>(1,
										 std::make_shared<VariableNode>("x"),
										 std::make_shared<ConstantNode>("12345"),
										 "12345")
	};

	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, "main");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"main", proc} };
	AST expected = std::make_shared<ProgramNode>(procMap);

	REQUIRE(*output == *expected);
}

TEST_CASE("Const validity 7.2 - const can be as long as possible") {
	std::vector<Token*> input = {
			new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
			new NameToken("x"), new TerminalToken("="),
			new IntegerToken("1234567890987654321234567890987654321"),
			new TerminalToken(";"), new TerminalToken("}"), new EndOfFileToken(),
	};
	SPParser parser = SPParser(input);
	AST output = parser.parseProgram();

	std::vector<std::shared_ptr<StmtNode>> stmts{
			std::make_shared<AssignNode>(1,
										 std::make_shared<VariableNode>("x"),
										 std::make_shared<ConstantNode>("1234567890987654321234567890987654321"),
										 "1234567890987654321234567890987654321")
	};

	std::shared_ptr<ProcedureNode> proc = std::make_shared<ProcedureNode>(stmts, "main");
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap{ {"main", proc} };
	AST expected = std::make_shared<ProgramNode>(procMap);

	REQUIRE(*output == *expected);
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Var_name validity 6.13 - var_name cannot start with a digit") {
	// procedure main { read 1main; }
	std::vector<Token*> input {
			new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
			new NameToken("read"), new IntegerToken("1"), new NameToken("main"),
			new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};;
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected a variable name but got '1' instead.\n");
}

TEST_CASE("Var_name validity 6.14 - var_name cannot have symbols") {
	// procedure main { read m*in; }
	std::vector<Token*> input {
			new NameToken("procedure"), new NameToken("main"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("m"), new TerminalToken("*"),
			new NameToken("in"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};;
	SPParser parser = SPParser(input);
	REQUIRE_THROWS_WITH(parser.parseProgram(), "Expected ';' but got '*' instead.\n");
}