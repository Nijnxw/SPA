#include "simple_parser/Token.h"
#include "simple_parser/Lexer.h"

#include "catch.hpp"
#include <sstream>

bool compareVectors(const std::vector<Token*> output, const std::vector<Token*> expected) {
	return std::equal(output.begin(), output.end(),
										expected.begin(), expected.end(),
										[](Token* t1, Token* t2) { return *t1 == *t2; });
}

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------

TEST_CASE("Test end of file token") {
	std::string program = "";
	std::istringstream input(program);

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = { new EndOfFileToken() };

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test NAME tokens") {
	std::string program = "procedure     ProCedure if read x1 X1 x1x x1X x";
	std::istringstream input(program);

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
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

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
			new IntegerToken("1"),     new IntegerToken("13"),
			new IntegerToken("0"),     new IntegerToken("100"),
			new IntegerToken("93"),   new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test OPERATOR tokens") {
	std::string program = "+ && = ! != < >=";
	std::istringstream input(program);

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
			new OperatorToken("+"), new OperatorToken("&&"),
			new OperatorToken("="), new OperatorToken("!"),
			new OperatorToken("!="), new OperatorToken("<"),
			new OperatorToken(">="), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test PUNCTUATOR tokens") {
	std::string program = "{ } ( ) ;";
	std::istringstream input(program);

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
			new PunctuatorToken("{"), new PunctuatorToken("}"),
			new PunctuatorToken("("), new PunctuatorToken(")"),
			new PunctuatorToken(";"), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test all lexical tokens") {
	std::string program = "if while procedure ( ) { } && variAble ball8 89 2 < <= = != print V1 ;";
	std::istringstream input(program);

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
			new NameToken("if"), new NameToken("while"),
			new NameToken("procedure"), new PunctuatorToken("("),
			new PunctuatorToken(")"), new PunctuatorToken("{"),
			new PunctuatorToken("}"), new OperatorToken("&&"),
			new NameToken("variAble"), new NameToken("ball8"),
			new IntegerToken("89"), new IntegerToken("2"),
			new OperatorToken("<"), new OperatorToken("<="),
			new OperatorToken("="), new OperatorToken("!="),
			new NameToken("print"), new NameToken("V1"),
			new PunctuatorToken(";"), new EndOfFileToken(),
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

	auto lexer = Lexer(&input);
	std::vector<Token*> output = lexer.tokenize();
	std::vector<Token*> expected = {
			new NameToken("procedure"), new NameToken("sumDigits"), new PunctuatorToken("{"),
			new NameToken("read"), new NameToken("number"), new PunctuatorToken(";"),
			new NameToken("sum"), new OperatorToken("="), new IntegerToken("0"),
			new PunctuatorToken(";"), new NameToken("while"), new PunctuatorToken("("),
			new NameToken("number"), new OperatorToken(">"), new IntegerToken("0"),
			new PunctuatorToken(")"), new PunctuatorToken("{"), new NameToken("digit"),
			new OperatorToken("="), new NameToken("number"), new OperatorToken("%"),
			new IntegerToken("10"), new PunctuatorToken(";"), new NameToken("sum"),
			new OperatorToken("="), new NameToken("sum"), new OperatorToken("+"),
			new NameToken("digit"), new PunctuatorToken(";"), new NameToken("number"),
			new OperatorToken("="), new NameToken("number"), new OperatorToken("/"),
			new IntegerToken("10"), new PunctuatorToken(";"), new PunctuatorToken("}"),
			new NameToken("print"), new NameToken("sum"), new PunctuatorToken(";"),
			new PunctuatorToken("}"), new EndOfFileToken(),
	};

	REQUIRE(compareVectors(output, expected));
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Test invalid symbols - underscore") {
	std::string program = "proc_name";
	std::istringstream input(program);
	auto lexer = Lexer(&input);
	REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test invalid symbols - '@'") {
	std::string program = "@";
	std::istringstream input(program);
	auto lexer = Lexer(&input);
	REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test next token is incorrect") {
	SECTION("& token") {
		std::string program = "&2";
		std::istringstream input(program);
		auto lexer = Lexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}

	SECTION("| token") {
		std::string program = "|>";
		std::istringstream input(program);
		auto lexer = Lexer(&input);
		REQUIRE_THROWS(lexer.tokenize());
	}
}