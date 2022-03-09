#include <simple_parser/CallStmtValidator.h>

#include "catch.hpp"

TEST_CASE("Catches calls to a non-existing procedure") {
	CallStmtValidator callStmtValidator = CallStmtValidator();
	callStmtValidator.addProcName("main");
	callStmtValidator.addProcCall("main", "main1");
	REQUIRE_THROWS_WITH(callStmtValidator.checkCallStmtsValidity(),
		"A procedure cannot call a non-existing procedure.\n");
}

TEST_CASE("Catches recursive calls") {
	CallStmtValidator callStmtValidator = CallStmtValidator();
	REQUIRE_THROWS_WITH(callStmtValidator.addProcCall("main", "main"),
		"Recursive calls are not allowed. Procedure 'main' tried to call itself.\n");
}

TEST_CASE("Catches cyclic calls - 2 procedures") {
	CallStmtValidator callStmtValidator = CallStmtValidator();
	callStmtValidator.addProcName("main1");
	callStmtValidator.addProcName("main2");
	callStmtValidator.addProcCall("main1", "main2");
	callStmtValidator.addProcCall("main2", "main1");
	REQUIRE_THROWS_WITH(callStmtValidator.checkCallStmtsValidity(),
		"Cyclic calls are not allowed.\n");
}

TEST_CASE("Catches cyclic calls - 3 procedures") {
	CallStmtValidator callStmtValidator = CallStmtValidator();
	callStmtValidator.addProcName("main1");
	callStmtValidator.addProcName("main2");
	callStmtValidator.addProcName("main3");
	callStmtValidator.addProcCall("main1", "main2");
	callStmtValidator.addProcCall("main2", "main3");
	callStmtValidator.addProcCall("main3", "main1");
	REQUIRE_THROWS_WITH(callStmtValidator.checkCallStmtsValidity(),
		"Cyclic calls are not allowed.\n");
}

TEST_CASE("Catches cyclic calls - 4 procedures") {
	CallStmtValidator callStmtValidator = CallStmtValidator();
	callStmtValidator.addProcName("main1");
	callStmtValidator.addProcName("main2");
	callStmtValidator.addProcName("main3");
	callStmtValidator.addProcName("main4");
	callStmtValidator.addProcCall("main1", "main2");
	callStmtValidator.addProcCall("main1", "main3");
	callStmtValidator.addProcCall("main2", "main3");
	callStmtValidator.addProcCall("main3", "main4");
	callStmtValidator.addProcCall("main4", "main1");
	REQUIRE_THROWS_WITH(callStmtValidator.checkCallStmtsValidity(),
		"Cyclic calls are not allowed.\n");
}