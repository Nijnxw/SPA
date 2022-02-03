#include "catch.hpp"
#include "pkb/stores/ModifiesStore.h"

TEST_CASE("ModifiesStore storage functionality") {
	EntityStore::clear();
	ModifiesStore::clear();
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
		*/
		// Assumed calls from SP/DE
		EntityStore::addStatementWithType(EntityType::READ, 1);
		EntityStore::addAssignStatement(2, "LHS", "RHS");
		EntityStore::addStatementWithType(EntityType::IF, 3);
		EntityStore::addAssignStatement(4, "LHS", "RHS");
		EntityStore::addStatementWithType(EntityType::WHILE, 5);
		EntityStore::addAssignStatement(6, "LHS", "RHS");
		ModifiesStore::addModifiesStatement(1, std::unordered_set<std::string>({"p"}));
		ModifiesStore::addModifiesStatement(2, std::unordered_set<std::string>({"a"}));
		ModifiesStore::addModifiesStatement(3, std::unordered_set<std::string>({"pattern", "w", "ifs", "a", "p", "x"}));
		ModifiesStore::addModifiesStatement(4, std::unordered_set<std::string>({"pattern"}));
		ModifiesStore::addModifiesStatement(5, std::unordered_set<std::string>({"w"}));
		ModifiesStore::addModifiesStatement(6, std::unordered_set<std::string>({"w"}));

		// Underscore RHS
		SECTION("Modifies(1,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("1", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Modifies(7,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("7", "_", EntityType::INT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Modifies(s,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("s", "_", EntityType::STMT, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"s", {"1", "2", "3", "4", "5", "6"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(a,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("a", "_", EntityType::ASSIGN, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"a", {"2", "4", "6"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(r,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("r", "_", EntityType::READ, EntityType::WILD, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"r", {"1"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(if,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("if", "_", EntityType::IF, EntityType::WILD, false);
			Table expectedTable = {{"if", {"3"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(w,'_') query") {
			QueryClauseTable res = ModifiesStore::getModifies("w", "_", EntityType::WHILE, EntityType::WILD, false);
			Table expectedTable = {{"w", {"5"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

			// Synonym RHS
		SECTION("Modifies(3, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("3", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {{"v", {"pattern", "w", "ifs", "a", "p", "x"}}};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(7, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("7", "v", EntityType::INT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Modifies(s, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("s", "v", EntityType::STMT, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s", {"1", "2", "3",       "3", "3",   "3", "3", "3", "4",       "5", "6"}},
				{"v", {"p", "a", "pattern", "w", "ifs", "a", "p", "x", "pattern", "w", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(a, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("a", "v", EntityType::ASSIGN, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"2", "4",       "6"}},
				{"v", {"a", "pattern", "w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(r, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("r", "v", EntityType::READ, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"r", {"1"}},
				{"v", {"p"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(if, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("if", "v", EntityType::IF, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"if", {"3",       "3", "3",   "3", "3", "3"}},
				{"v",  {"pattern", "w", "ifs", "a", "p", "x"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(w, v) query") {
			QueryClauseTable res = ModifiesStore::getModifies("w", "v", EntityType::WHILE, EntityType::VAR, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"w", {"5"}},
				{"v", {"w"}}
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

			// Variable RHS
		SECTION("Modifies(5, 'w') query") {
			QueryClauseTable res = ModifiesStore::getModifies("5", "w", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
		}

		SECTION("Modifies(2, 'w') query") {
			QueryClauseTable res = ModifiesStore::getModifies("2", "w", EntityType::INT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == false);
		}

		SECTION("Modifies(s, 'w') query") {
			QueryClauseTable res = ModifiesStore::getModifies("s", "w", EntityType::STMT, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"s", {"3", "5", "6"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(a, 'pattern') query") {
			QueryClauseTable res = ModifiesStore::getModifies("a", "pattern", EntityType::ASSIGN, EntityType::STRING,
															  false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"a", {"4"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(r, 'p') query") {
			QueryClauseTable res = ModifiesStore::getModifies("r", "p", EntityType::READ, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"r", {"1"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(if, 'x') query") {
			QueryClauseTable res = ModifiesStore::getModifies("if", "x", EntityType::IF, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"if", {"3"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}

		SECTION("Modifies(w, 'w') query") {
			QueryClauseTable res = ModifiesStore::getModifies("w", "w", EntityType::WHILE, EntityType::STRING, false);
			REQUIRE(res.getBooleanResult() == true);
			Table expectedTable = {
				{"w", {"5"}},
			};
			REQUIRE(res == QueryClauseTable(expectedTable));
		}
	}
	EntityStore::clear();
	ModifiesStore::clear();
}
