#include "catch.hpp"
#include "../src/util/RPN.h"

TEST_CASE("Correct Handling of Single Numbers") {
	REQUIRE_NOTHROW(RPN("1"));
	REQUIRE_NOTHROW(RPN("999"));
}

TEST_CASE("Correct Handling of Variables") {
	REQUIRE_NOTHROW(RPN("abc"));
	REQUIRE_NOTHROW(RPN("a11"));
}

TEST_CASE("Correct Handling of Expressions") {
	std::vector<std::string> expected;

	REQUIRE_NOTHROW(RPN("1+2+3"));
	RPN rpn1("1+2+3");
	expected = { "1", "2", "+", "3", "+" };
	REQUIRE(rpn1.getRpnNotation() == expected);

	REQUIRE_NOTHROW(RPN("11-2+3"));
	RPN rpn2("11-2+3");
	expected = { "11", "2", "-", "3", "+" };
	REQUIRE(rpn2.getRpnNotation() == expected);

	REQUIRE_NOTHROW(RPN("a+b+c"));
	RPN rpn3("a+b+c");
	expected = { "a", "b", "+", "c", "+" };
	REQUIRE(rpn3.getRpnNotation() == expected);
}

TEST_CASE("Correct Handling of Whitespace") {
	std::vector<std::string> expected;

	REQUIRE_THROWS_WITH(RPN(""), "No tokens Detected.\n");
	REQUIRE_THROWS_WITH(RPN(" "), "No tokens Detected.\n");
	REQUIRE_THROWS_WITH(RPN("	"), "No tokens Detected.\n");

	REQUIRE_NOTHROW(RPN("1 + 1"));
	RPN rpn3("1 + 1");
	expected = { "1", "1", "+" };
	REQUIRE(rpn3.getRpnNotation() == expected);
}

TEST_CASE("Correct Handling of Terms") {
	std::vector<std::string> expected;

	REQUIRE_NOTHROW(RPN("1 * 3 / 1"));
	RPN rpn1("1 * 3 / 1");
	expected = { "1", "3", "*", "1", "/" };
	REQUIRE(rpn1.getRpnNotation() == expected);

	REQUIRE_NOTHROW(RPN("1 * 2 + 3 / 1"));
	RPN rpn2("1 * 2 + 3 / 1");
	expected = { "1", "2", "*", "3", "1", "/", "+" };
	REQUIRE(rpn2.getRpnNotation() == expected);

	REQUIRE_NOTHROW(RPN("1 * 2 * 3 + 1"));
	RPN rpn3("1 * 2 * 3 + 1");
	expected = { "1", "2", "*", "3", "*", "1", "+" };
	REQUIRE(rpn3.getRpnNotation() == expected);

	REQUIRE_NOTHROW(RPN("a * b + c / 1"));
	RPN rpn4("a * b + c / 1");
	expected = { "a", "b", "*", "c", "1", "/", "+" };
	REQUIRE(rpn4.getRpnNotation() == expected);
}

TEST_CASE("Invalid Token Name") {
	REQUIRE_THROWS_WITH(RPN("^% + #$"), "Invalid Token Detected in Statement.\n");
}
