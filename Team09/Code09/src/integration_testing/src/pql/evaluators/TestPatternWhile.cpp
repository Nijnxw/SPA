#include "catch.hpp"
#include "PQL/evaluators/PatternWhileEvaluator.h"
#include "models/EntityType.h"

TEST_CASE("While Pattern API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	PatternWhileEvaluator patternWhileEvaluator = PatternWhileEvaluator();

	// Populating PKB information based on STANDARD_source.txt
	SECTION("Initialization of program variables") {
		std::unordered_set<std::string> conditionalVariables = { "a", "false"};
		PKB::addWhileStatement(7, conditionalVariables);

		// --------------------------------------------------
		//                  LHS synonym
		// --------------------------------------------------
		// getWhilePattern(LHS synonym)
		SECTION("pattern w(v, _) positive query") {
			QueryClauseResult res = patternWhileEvaluator.getWhilePattern("v", "w", EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"w", {"7", "7"}},
				{"v", {"a", "false"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS variable
		// --------------------------------------------------
		// getWhilePattern(LHS variable)
		SECTION("pattern w(a, _) positive query") {
			QueryClauseResult res = patternWhileEvaluator.getWhilePattern("a", "w", EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"w", {"7"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern w(x, _, _) positive query") {
			QueryClauseResult res = patternWhileEvaluator.getWhilePattern("x", "w", EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  LHS wild card
		// --------------------------------------------------
		// getWhilePattern(LHS wild card)
		SECTION("pattern w(_, _) positive query") {
			QueryClauseResult res = patternWhileEvaluator.getWhilePattern("_", "w", EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"w", {"7"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
	}
	PKB::clearAllStores();
}
