#include "catch.hpp"
#include "../src/RPN.h"

TEST_CASE("testing") {
	RPN rpn("1+1");
	REQUIRE(rpn.getInfixNotation() == "1+1");
	REQUIRE(rpn.getRpnNotation() == "test");
}