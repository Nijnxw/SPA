#include "catch.hpp"
#include "PQL/evaluators/ModifiesEvaluator.h"

TEST_CASE("Test ModifiesStore and ModifiesEvaluator functionality") {
	PKB::clearAllStores();
	ModifiesEvaluator modifiesEvaluator = ModifiesEvaluator();

	SECTION("populate pkb with test simple program and retrieve with") {
		/*
			Test Simple Program
			procedure testProg {
			1    read p;
			2    a = p * 2;
			3    if (c == k) then {
			4        pattern = p * a * a + p * ifs + p * w;
			5        while(w > 0) {
			6            w = w - 1;
					}
			}
			procedure testProg2 {
			7    call testProg1;
			8    an = p;
			}
		*/
		// Assumed calls from SP/DE
		PKB::addStatementWithType(EntityType::READ, 1);
		PKB::addAssignStatement(2, "<LHS>", "<RHS>");
		PKB::addStatementWithType(EntityType::IF, 3);
		PKB::addAssignStatement(4, "<LHS>", "<RHS>");
		PKB::addStatementWithType(EntityType::WHILE, 5);
		PKB::addAssignStatement(6, "<LHS>", "<RHS>");
		PKB::addStatementWithType(EntityType::CALL, 7);
		PKB::addAssignStatement(8, "<LHS>", "<RHS>");
		PKB::addModifiesStatement(1, {"p"});
		PKB::addModifiesStatement(2, {"a"});
		PKB::addModifiesStatement(3, {"pattern", "w" });
		PKB::addModifiesStatement(4, {"pattern"});
		PKB::addModifiesStatement(5, {"w"});
		PKB::addModifiesStatement(6, {"w"});
		PKB::addModifiesStatement(7, {"p", "a", "pattern", "w"});
		PKB::addModifiesStatement(8, {"an"});
		PKB::addModifiesProcedure("testProg", {"p", "a", "pattern", "w"});
		PKB::addModifiesProcedure("testProg2", {"p", "a", "pattern", "w", "an"});

		// Underscore RHS
		SECTION("Modifies(1, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Modifies(9, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("9", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Modifies(s, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"s", {"1", "2", "3", "4", "5", "6", "7", "8"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(a, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("a", "_", EntityType::ASSIGN, EntityType::WILD,
																  false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"a", {"2", "4", "6", "8"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(r, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("r", "_", EntityType::READ, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"r", {"1"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(if, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("if", "_", EntityType::IF, EntityType::WILD, false);
			Table expectedTable = {{"if", {"3"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(w, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("w", "_", EntityType::WHILE, EntityType::WILD, false);
			Table expectedTable = {{"w", {"5"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}
		
		SECTION("Modifies(c, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("c", "_", EntityType::CALL, EntityType::WILD, false);
			Table expectedTable = { {"c", {"7"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("proc", "_", EntityType::PROC, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"proc", { "testProg", "testProg2"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc_name, _) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("testProg2", "_", EntityType::STRING, EntityType::WILD, false);
			REQUIRE(res.containsValidResult() == true);
		}

		// Synonym RHS
		SECTION("Modifies(3, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("3", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {{"v", {"pattern", "w"}}};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(7, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("7", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = { {"v", {"p", "a", "pattern", "w"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(s, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("s", "v", EntityType::STMT, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", {"1", "2", "3",       "3", "4",       "5", "6", "7", "7", "7",       "7", "8"}},
				{"v", {"p", "a", "pattern", "w", "pattern", "w", "w", "p", "a", "pattern", "w", "an"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(a, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("a", "v", EntityType::ASSIGN, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"2", "4",       "6", "8"}},
				{"v", {"a", "pattern", "w", "an"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(r, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("r", "v", EntityType::READ, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"r", {"1"}},
				{"v", {"p"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(if, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("if", "v", EntityType::IF, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"if", {"3",       "3"}},
				{"v",  {"pattern", "w"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(w, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("w", "v", EntityType::WHILE, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"w", {"5"}},
				{"v", {"w"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(c, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("c", "v", EntityType::CALL, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"c", {"7", "7", "7",       "7"}},
				{"v", {"p", "a", "pattern", "w"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("proc", "v", EntityType::PROC, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"proc", {"testProg", "testProg", "testProg", "testProg", "testProg2", "testProg2", "testProg2", "testProg2", "testProg2"}},
				{"v",    {"p"       , "a"       , "pattern" , "w"       , "p"        , "a"       , "pattern",      "w",       "an"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc_name, v) query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("testProg2", "v", EntityType::STRING, EntityType::VAR, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"v", { "p" , "a" , "pattern", "w", "an"}}
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}


		// Variable RHS
		SECTION("Modifies(5, 'w') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("5", "w", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}

		SECTION("Modifies(2, 'w') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("2", "w", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == false);
		}

		SECTION("Modifies(s, 'w') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("s", "w", EntityType::STMT, EntityType::STRING,
																  false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"s", {"3", "5", "6", "7"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(a, 'pattern') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("a", "pattern", EntityType::ASSIGN,
																  EntityType::STRING,
																  false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"a", {"4"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(r, 'p') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("r", "p", EntityType::READ, EntityType::STRING,
																  false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"r", {"1"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(if, 'w') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("if", "w", EntityType::IF, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"if", {"3"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(w, 'w') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("w", "w", EntityType::WHILE, EntityType::STRING,
																  false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"w", {"5"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(c, 'pattern') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("c", "pattern", EntityType::CALL, EntityType::STRING, false);
			Table expectedTable = { {"c", {"7"}} };
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc, 'x') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("proc", "w", EntityType::PROC, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
			Table expectedTable = {
				{"proc", {"testProg", "testProg2"}},
			};
			REQUIRE(res == QueryClauseResult(expectedTable));
		}

		SECTION("Modifies(proc_name, 'x') query") {
			QueryClauseResult res = modifiesEvaluator.getModifies("testProg2", "an", EntityType::STRING, EntityType::STRING, false);
			REQUIRE(res.containsValidResult() == true);
		}
	}
	PKB::clearAllStores();
}
