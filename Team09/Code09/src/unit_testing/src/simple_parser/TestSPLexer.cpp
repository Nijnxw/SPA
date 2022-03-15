#include "simple_parser/SPToken.h"
#include "simple_parser/SPLexer.h"

#include "catch.hpp"
#include <sstream>

bool compareVectors(const std::vector<SPToken*>& output, const std::vector<SPToken*>& expected) {
	return std::equal(output.begin(), output.end(),
										expected.begin(), expected.end(),
										[](SPToken* t1, SPToken* t2) { return *t1 == *t2; });
}

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------

TEST_CASE("Test end of file token") {
	std::string program;
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {new EndOfFileToken() };

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test NAME tokens") {
	std::string program = "procedure     ProCedure if read x1 X1 x1x x1X x";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new NameToken("procedure"), new NameToken("ProCedure"),
			new NameToken("if"),        new NameToken("read"),
			new NameToken("x1"),        new NameToken("X1"),
			new NameToken("x1x"),       new NameToken("x1X"),
			new NameToken("x"),         new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test INTEGER tokens") {
	std::string program = "1  13 0 	100 93";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new IntegerToken("1"),     new IntegerToken("13"),
			new IntegerToken("0"),     new IntegerToken("100"),
			new IntegerToken("93"),   new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test OPERATOR tokens") {
	std::string program = "+ && = ! != < >=";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new TerminalToken("+"), new TerminalToken("&&"),
			new TerminalToken("="), new TerminalToken("!"),
			new TerminalToken("!="), new TerminalToken("<"),
			new TerminalToken(">="), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test PUNCTUATOR tokens") {
	std::string program = "{ } ( ) ;";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new TerminalToken("{"), new TerminalToken("}"),
			new TerminalToken("("), new TerminalToken(")"),
			new TerminalToken(";"), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test all lexical tokens") {
	std::string program = "if while procedure ( ) { } && variAble ball8 89 2 < <= = != print V1 ;";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new NameToken("if"), new NameToken("while"),
			new NameToken("procedure"), new TerminalToken("("),
			new TerminalToken(")"), new TerminalToken("{"),
			new TerminalToken("}"), new TerminalToken("&&"),
			new NameToken("variAble"), new NameToken("ball8"),
			new IntegerToken("89"), new IntegerToken("2"),
			new TerminalToken("<"), new TerminalToken("<="),
			new TerminalToken("="), new TerminalToken("!="),
			new NameToken("print"), new NameToken("V1"),
			new TerminalToken(";"), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test SIMPLE program") {
	std::string program = R"(
	procedure sumDigits {
			read number;
			sum = 0;

			while (number > 0) {
					digit = number % 10;
					sum = sum + digit;
					number = number / 10;
			}

			print sum;
	}
	)";
	std::istringstream input(program);

	auto lexer = SPLexer(&input);
	std::vector<SPToken*> output = lexer.tokenize();
	std::vector<SPToken*> expected = {
			new NameToken("procedure"), new NameToken("sumDigits"), new TerminalToken("{"),
			new NameToken("read"), new NameToken("number"), new TerminalToken(";"),
			new NameToken("sum"), new TerminalToken("="), new IntegerToken("0"),
			new TerminalToken(";"), new NameToken("while"), new TerminalToken("("),
			new NameToken("number"), new TerminalToken(">"), new IntegerToken("0"),
			new TerminalToken(")"), new TerminalToken("{"), new NameToken("digit"),
			new TerminalToken("="), new NameToken("number"), new TerminalToken("%"),
			new IntegerToken("10"), new TerminalToken(";"), new NameToken("sum"),
			new TerminalToken("="), new NameToken("sum"), new TerminalToken("+"),
			new NameToken("digit"), new TerminalToken(";"), new NameToken("number"),
			new TerminalToken("="), new NameToken("number"), new TerminalToken("/"),
			new IntegerToken("10"), new TerminalToken(";"), new TerminalToken("}"),
			new NameToken("print"), new NameToken("sum"), new TerminalToken(";"),
			new TerminalToken("}"), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Test invalid integer - all zeroes") {
	std::string program = "0000";
	std::istringstream input(program);
	auto lexer = SPLexer(&input);
	REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test invalid integer - leading zeroes") {
	SECTION("one leading zero") {
		std::string program = "01";
		std::istringstream input(program);
		auto lexer = SPLexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}

	SECTION("multiple leading zeroes") {
		std::string program = "0000123";
		std::istringstream input(program);
		auto lexer = SPLexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}
}

TEST_CASE("Test invalid symbols - underscore") {
	std::string program = "proc_name";
	std::istringstream input(program);
	auto lexer = SPLexer(&input);
	REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test invalid symbols - '@'") {
	std::string program = "@";
	std::istringstream input(program);
	auto lexer = SPLexer(&input);
	REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test next token is incorrect") {
	SECTION("& token") {
		std::string program = "&2";
		std::istringstream input(program);
		auto lexer = SPLexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}

	SECTION("| token") {
		std::string program = "|>";
		std::istringstream input(program);
		auto lexer = SPLexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}
}