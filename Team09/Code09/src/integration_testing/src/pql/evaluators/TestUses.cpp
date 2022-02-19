#include "catch.hpp"
#include "PQL/evaluators/UsesEvaluator.h"

TEST_CASE("Test UsesStore and UsesEvaluator functionality") {
	PKB::clearAllStores();
	UsesEvaluator usesEvaluator = UsesEvaluator();

	SECTION("populate pkb with test simple program and retrieve with") {
		/*
			Test Simple Program
			procedure testProg {
			1    print p;
			2    a = p * 2;
			3    if (c == k) then {
			4        pattern = p * a * a + p * ifs + p * w;
				}
				else {
			5        read k;
				}
			}
		*/
		// Assumed calls from SP/DE
		PKB::addStatementWithType(EntityType::PRINT, 1);
		PKB::addAssignStatement(2, "LHS", "RHS");
		PKB::addStatementWithType(EntityType::IF, 3);
		PKB::addAssignStatement(4, "LHS", "RHS");
		PKB::addStatementWithType(EntityType::READ, 5);
		PKB::addUsesStatement(1, std::unordered_set<std::string>({"p"}));
		PKB::addUsesStatement(2, std::unordered_set<std::string>({"p"}));
		PKB::addUsesStatement(3, std::unordered_set<std::string>({"c", "k", "a", "p", "ifs", "w"}));
		PKB::addUsesStatement(4, std::unordered_set<std::string>({"a", "p", "ifs", "w"}));

		// Underscore RHS
		SECTION("Uses(1,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Uses(5,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("5", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Uses(s,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"s", {"1", "2", "3", "4"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(a,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("a", "_", EntityType::ASSIGN, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"a", {"2", "4"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(p,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("p", "_", EntityType::PRINT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"p", {"1"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(if,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("if", "_", EntityType::IF, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"if", {"3"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(w,'_') query") {
			QueryClauseTable res = usesEvaluator.getUses("w", "_", EntityType::WHILE, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

			// Synonym RHS
		SECTION("Uses(1, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("1", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"v", {"p"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(5, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("5", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Uses(s, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("s", "v", EntityType::STMT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s", {"1", "2", "3", "3", "3", "3", "3",   "3", "4", "4", "4",   "4"}},
				{"v", {"p", "p", "c", "k", "a", "p", "ifs", "w", "a", "p", "ifs", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(a, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("a", "v", EntityType::ASSIGN, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2", "4", "4", "4",   "4"}},
				{"v", {"p", "a", "p", "ifs", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(p, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("p", "v", EntityType::PRINT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"p", {"1"}},
				{"v", {"p"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(if, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("if", "v", EntityType::IF, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"if", {"3", "3", "3", "3", "3",   "3"}},
				{"v",  {"c", "k", "a", "p", "ifs", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(w, v) query") {
			QueryClauseTable res = usesEvaluator.getUses("w", "v", EntityType::WHILE, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == false);
		}


			// Variable RHS
		SECTION("Uses(3, 'k') query") {
			QueryClauseTable res = usesEvaluator.getUses("3", "k", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Uses(2, 'x') query") {
			QueryClauseTable res = usesEvaluator.getUses("2", "x", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Uses(s, 'a') query") {
			QueryClauseTable res = usesEvaluator.getUses("s", "a", EntityType::STMT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s", {"3", "4"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(a, 'ifs') query") {
			QueryClauseTable res = usesEvaluator.getUses("a", "ifs", EntityType::ASSIGN, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"4"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(p, 'p') query") {
			QueryClauseTable res = usesEvaluator.getUses("p", "p", EntityType::PRINT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"p", {"1"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(if, 'w') query") {
			QueryClauseTable res = usesEvaluator.getUses("if", "w", EntityType::IF, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"if", {"3"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Uses(w, 'k') query") {
			QueryClauseTable res = usesEvaluator.getUses("w", "k", EntityType::WHILE, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

	}
	PKB::clearAllStores();
}
