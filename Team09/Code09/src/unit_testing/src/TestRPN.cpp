#include "catch.hpp"
#include "../src/RPN.h"

TEST_CASE("testing") {
	RPN rpn("11+ 1+1");
	REQUIRE(rpn.getInfixNotation() == "11+ 1+1");
	REQUIRE(rpn.getRpnNotation() == "11+1");
}