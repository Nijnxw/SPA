#include "catch.hpp"
#include "PQL/evaluators/CallsEvaluator.h"

TEST_CASE("Calls Relationship API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	CallsEvaluator callsEvaluator = CallsEvaluator();

	/*
	procedure First{
	01	read x;
	02	read z;
	03	call Second; }

	procedure Second{
	04        x = 0;
	05        i = 5;
	06        while (i != 0) {
	07            x = x + 2 * y;
	08            call Third;
	09            i = i - 1;
	 }
	10        if (x == 1) then {
	11            x = x + 1; }
			  else {
	12            z = 1;
	 }
	13        z = z + x + i;
	14        y = z + 2;
	15        x = x * y + z; }

	procedure Third{
	16	z = 5;
	17	v = z;
	18	prstd::string v; }
	*/

	// Populating PKB information based on wiki code
	SECTION("Initialization of program variables") {
		PKB::addCalls("First", "Second");
		PKB::addCalls("Second", "Third");

		PKB::addCallsT("First", "Second");
		PKB::addCallsT("Second", "Third");
		PKB::addCallsT("First", "Third");

		// --------------------------------------------------
		//                  LHS string
		// --------------------------------------------------
		// getCalls(LHS string, RHS string)
		SECTION("Calls(First, Second) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("First", "Second", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Calls(Second, First) negative query - invalid ordering") {
			QueryClauseResult res = callsEvaluator.getCalls("Second", "First", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Calls(First, Third) negative query - only for transitive") {
			QueryClauseResult res = callsEvaluator.getCalls("First", "Third", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCallsT(LHS string, RHS string)
		SECTION("CallsT(First, Second) positive query - normal") {
			QueryClauseResult res = callsEvaluator.getCallsT("First", "Second", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("CallsT(First, Third) positive query - only for transitive") {
			QueryClauseResult res = callsEvaluator.getCallsT("First", "Third", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("CallsT(Second, First) negative query - invalid ordering") {
			QueryClauseResult res = callsEvaluator.getCallsT("Second", "First", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCalls(LHS string, RHS proc)
		SECTION("Calls(First, p) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("First", "p", EntityType::STRING, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"Second"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Calls(Third, p) negative query") {
			QueryClauseResult res = callsEvaluator.getCalls("Third", "p", EntityType::STRING, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCallsT(LHS string, RHS proc)
		SECTION("CallsT(First, p) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("First", "p", EntityType::STRING, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"p", {"Second", "Third"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("CallsT(Third, p) negative query") {
			QueryClauseResult res = callsEvaluator.getCallsT("Third", "p", EntityType::STRING, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCalls(LHS string, RHS wild)
		SECTION("Calls(First, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("First", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Calls(Third, _) negative query") {
			QueryClauseResult res = callsEvaluator.getCalls("Third", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCallsT(LHS string, RHS wild)
		SECTION("CallsT(First, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("First", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("CallsT(Third, _) negative query") {
			QueryClauseResult res = callsEvaluator.getCallsT("Third", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  LHS proc
		// --------------------------------------------------
		// getCalls(LHS proc, RHS string)
		SECTION("Calls(p, Third) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("p", "Third", EntityType::PROC, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"Second"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Calls(p, First) negative query - invalid ordering") {
			QueryClauseResult res = callsEvaluator.getCalls("p", "First", EntityType::PROC, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCallsT(LHS proc, RHS string)
		SECTION("CallsT(p, Third) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("p", "Third", EntityType::PROC, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"p", {"First", "Second"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("CallsT(p, First) negative query - invalid ordering") {
			QueryClauseResult res = callsEvaluator.getCallsT("p", "First", EntityType::PROC, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCalls(LHS proc, RHS proc)
		SECTION("Calls(p1, p2) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("p1", "p2", EntityType::PROC, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p1", {"First", "Second"}},
				{"p2", {"Second", "Third"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getCallsT(LHS proc, RHS proc)
		SECTION("CallsT(p1, p2) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("p1", "p2", EntityType::PROC, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"p1", {"First", "First", "Second"}},
				{"p2", {"Second", "Third", "Third"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getCalls(LHS proc, RHS wild)
		SECTION("Calls(p, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("p", "_", EntityType::PROC, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"First", "Second"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getCallsT(LHS proc, RHS wild)
		SECTION("CallsT(p, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("p", "_", EntityType::PROC, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"First", "Second"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS wild
		// --------------------------------------------------
		// getCalls(LHS wild, RHS string)
		SECTION("Calls(_, Second) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("_", "Second", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Calls(_, First) negative query") {
			QueryClauseResult res = callsEvaluator.getCalls("_", "First", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCallsT(LHS wild, RHS string)
		SECTION("CallsT(_, Second) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("_", "Second", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("CallsT(_, First) negative query") {
			QueryClauseResult res = callsEvaluator.getCallsT("_", "First", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getCalls(LHS wild, RHS proc)
		SECTION("Calls(_, p) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("_", "p", EntityType::WILD, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"Second", "Third"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getCallsT(LHS wild, RHS proc)
		SECTION("CallsT(_, p) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("_", "p", EntityType::WILD, EntityType::PROC, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"p", {"Second", "Third"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// getCalls(LHS wild, RHS wild)
		SECTION("Calls(_, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCalls("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		// getCallsT(LHS wild, RHS wild)
		SECTION("CallsT(_, _) positive query") {
			QueryClauseResult res = callsEvaluator.getCallsT("_", "_", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}
	}
	PKB::clearAllStores();
}
