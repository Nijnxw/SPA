#include "catch.hpp"
#include "../src/util/RPN.h"

TEST_CASE("Correct Handling of Single Numbers") {
	REQUIRE_NOTHROW(RPN("1"));
	REQUIRE_NOTHROW(RPN("999"));
}

TEST_CASE("Correct Handling of Terms") {
	REQUIRE_NOTHROW(RPN("1+2+3"));
	RPN rpn1("1+2+3");
	REQUIRE(rpn1.getRpnNotation() == "1,2,+,3,+");
	REQUIRE_NOTHROW(RPN("11-2+3"));
	RPN rpn2("11-2+3");
	REQUIRE(rpn2.getRpnNotation() == "11,2,-,3,+");
}

TEST_CASE("Correct Handling of Whitespace") {
	REQUIRE_NOTHROW(RPN(""));
	RPN rpn1("");
	REQUIRE(rpn1.getRpnNotation() == "");
	REQUIRE_NOTHROW(RPN(" "));
	RPN rpn2(" ");
	REQUIRE(rpn2.getRpnNotation() == "");
	REQUIRE_NOTHROW(RPN("1 + 1"));
	RPN rpn3("1 + 1");
	REQUIRE(rpn3.getRpnNotation() == "1,1,+");
}

TEST_CASE("Invalid Token Throws Exception") {
	REQUIRE_THROWS(RPN("a"));
}
