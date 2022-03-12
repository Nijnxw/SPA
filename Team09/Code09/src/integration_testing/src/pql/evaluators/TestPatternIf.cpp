#include "catch.hpp"
#include "PQL/evaluators/PatternIfEvaluator.h"
#include "models/EntityType.h"

TEST_CASE("If Pattern API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	PatternIfEvaluator patternIfEvaluator = PatternIfEvaluator();

	// Populating PKB information based on STANDARD_source.txt
	SECTION("Initialization of program variables") {
		std::unordered_set<std::string> conditionalVariables = { "true" };
		PKB::addIfStatement(4, conditionalVariables);

		// --------------------------------------------------
		//                  LHS synonym
		// --------------------------------------------------
		// getIfPattern(LHS synonym)
		SECTION("pattern ifs(v, _, _) positive query") {
			QueryClauseResult res = patternIfEvaluator.getIfPattern("v", "ifs", EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"ifs", { "4"}},
				{"v", {"true"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS variable
		// --------------------------------------------------
		// getIfPattern(LHS variable)
		SECTION("pattern ifs(true, _, _) positive query") {
			QueryClauseResult res = patternIfEvaluator.getIfPattern("true", "ifs", EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"ifs", {"4"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern ifs(x, _, _) positive query") {
			QueryClauseResult res = patternIfEvaluator.getIfPattern("x", "ifs", EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  LHS wild card
		// --------------------------------------------------
		// getIfPattern(LHS wild card)
		SECTION("pattern ifs(_, _, _) positive query") {
			QueryClauseResult res = patternIfEvaluator.getIfPattern("_", "ifs", EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"ifs", {"4"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
	}
	PKB::clearAllStores();
}
