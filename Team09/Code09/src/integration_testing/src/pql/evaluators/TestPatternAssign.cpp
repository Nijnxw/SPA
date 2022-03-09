#include "catch.hpp"
#include "PQL/evaluators/PatternAssignEvaluator.h"
#include "models/EntityType.h"

TEST_CASE("Assignment Pattern API") {
	// The same store is reused through tests, so clearing is a must.
	PKB::clearAllStores();
	PatternAssignEvaluator patternAssignEvaluator = PatternAssignEvaluator();

	// Populating PKB information based on sample_SIMPLE.txt
	SECTION("Initialization of program variables") {
		PKB::addAssignStatement(2, "a", "p 2 *");
		PKB::addAssignStatement(4, "pattern", "p a * a * p ifs * + p w * +");
		PKB::addAssignStatement(6, "w", "w 1 -");

		// --------------------------------------------------
		//                  LHS synonym
		// --------------------------------------------------
		// getPattern(LHS synonym, RHS wild card match)
		SECTION("pattern a(v, _p_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "_p_", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2", "4"}},
				{"v", {"a", "pattern"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, _2_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "_2_", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, _p 2 *_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "_p 2 *_", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, _x_) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "_x_", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS synonym, RHS exact match)
		SECTION("pattern a(v, p 2 *) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "p 2 *", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2"}},
				{"v", {"a"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, p a * a * p ifs * + p w * +) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "p a * a * p ifs * + p w * +", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"4"}},
				{"v", {"pattern"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, w 1 -) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "w 1 -", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"6"}},
				{"v", {"w"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(v, p) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "p", "a", EntityType::VAR, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS synonym, RHS wild card)
		SECTION("pattern a(v, _) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("v", "_", "a", EntityType::VAR, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2", "4", "6"}},
				{"v", {"a", "pattern", "w"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		// --------------------------------------------------
		//                  LHS variable
		// --------------------------------------------------
		// getPattern(LHS variable, RHS wild card match)
		SECTION("pattern a(a, _p_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("a", "_p_", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(a, _p 2 *_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("a", "_p 2 *_", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(x, _p_) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("x", "_p_", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS variable, RHS exact match)
		SECTION("pattern a(a, p 2 *) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("a", "p 2 *", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(pattern, p a * a * p ifs * + p w * +) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("pattern", "p a * a * p ifs * + p w * +", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"4"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(w, w 1 -) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("w", "w 1 -", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(x, w 1 -) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("x", "w 1 -", "a", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS variable, RHS wildcard)
		SECTION("pattern a(a, _) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("a", "_", "a", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(pattern, _) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("pattern", "_", "a", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"4"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(w, _) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("w", "_", "a", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(x, _) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("x", "_", "a", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// --------------------------------------------------
		//                  LHS wild card
		// --------------------------------------------------
		// getPattern(LHS wild card, RHS wild card match)
		SECTION("pattern a(_, _p_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "_p_", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2", "4"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(_, _p 2 *_) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "_p 2 *_", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(_, _x_) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "_x_", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS wild card, RHS exact match)
		SECTION("pattern a(_, p 2 *) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "p 2 *", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(_, w 1 -) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "w 1 -", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"6"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("pattern a(_, p) negative query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "p", "a", EntityType::WILD, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		// getPattern(LHS wildcard, RHS wildcard)
		SECTION("pattern a(_, _) positive query") {
			QueryClauseResult res = patternAssignEvaluator.getPattern("_", "_", "a", EntityType::WILD, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"a", {"2", "4", "6"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
	}
	PKB::clearAllStores();
}
