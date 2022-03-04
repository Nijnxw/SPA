#include "catch.hpp"
#include "pkb/stores/ModifiesStore.h"

TEST_CASE("ModifiesStore API") {
	ModifiesStore modifiesStore;
	modifiesStore.clear();

	// Populating PKB information based on simplestSIMPLE.txt
	SECTION("Initialization of program variables") {
		modifiesStore.addStmtVarRelationship(1, { "a" });
		modifiesStore.addStmtVarRelationship(2, { "r" });
		modifiesStore.addStmtVarRelationship(5, { "such" });
		modifiesStore.addStmtVarRelationship(6, { "pattern" });
		modifiesStore.addStmtVarRelationship(8, { "aPlus" });
		modifiesStore.addStmtVarRelationship(9, { "d" });
		modifiesStore.addProcVarRelationship("simplestSIMPLE", { "a", "r", "such", "pattern", "aPlus", "d" });

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------

		SECTION("getStmtInRelationship() positive query") {
			std::unordered_set<int> res = modifiesStore.getStmtInRelationship();
			std::unordered_set<int> expectedSet = { 1, 2, 5, 6, 8, 9 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarInRelationship() positive query") {
			std::unordered_set<std::string> res = modifiesStore.getVarInRelationship();
			std::unordered_set<std::string> expectedSet = { "a", "r", "such", "pattern", "aPlus", "d" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getStmtToVarRelationship() positive query") {
			std::unordered_map<int, std::unordered_set<std::string>> res = modifiesStore.getStmtToVarRelationship();
			std::unordered_map<int, std::unordered_set<std::string>> expectedSet = {
				{1, { "a" }},
				{2, { "r" }},
				{5, { "such" }},
				{6, { "pattern" }},
				{8, { "aPlus" }},
				{9, { "d" }},
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarToStmtRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<int>> res = modifiesStore.getVarToStmtRelationship();
			std::unordered_map<std::string, std::unordered_set<int>> expectedSet = {
				{"a", { 1 }},
				{"r", { 2 }},
				{"such", { 5 }},
				{"pattern", { 6 }},
				{"aPlus", { 8 }},
				{"d", { 9 }},
			};
			REQUIRE(res == expectedSet);
		}
		SECTION("getVarByStmt() positive query") {
			std::unordered_set<std::string> res = modifiesStore.getVarByStmt(6);
			std::unordered_set<std::string> expectedSet = { "pattern" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByStmt() negative query - invalid statement number") {
			std::unordered_set<std::string> res = modifiesStore.getVarByStmt(20);
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}
		
		
		SECTION("getStmtByVar() positive query") {
			std::unordered_set<int> res = modifiesStore.getStmtByVar("d");
			std::unordered_set<int> expectedSet = { 9 };
			REQUIRE(res == expectedSet);
		}
		
		SECTION("getStmtToVarByStmts() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = modifiesStore.getStmtToVarByStmts({ 1, 2, 5 });
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("1");
			secondColumn.push_back("a");
			firstColumn.push_back("2");
			secondColumn.push_back("r");
			firstColumn.push_back("5");
			secondColumn.push_back("such");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set = 
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
		
		SECTION("getStmtToVarByStmts() negative query with invalid statement numbers") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = modifiesStore.getStmtToVarByStmts({ 5, 6, 7, 20, 21, 22 });
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("5");
			secondColumn.push_back("such");
			firstColumn.push_back("6");
			secondColumn.push_back("pattern");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}
		
		SECTION("getProcInRelationship() positive query") {
			std::unordered_set<std::string> res = modifiesStore.getProcInRelationship();
			std::unordered_set<std::string> expectedSet = { "simplestSIMPLE" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcToVarRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<std::string>> res = modifiesStore.getProcToVarRelationship();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedSet = {
				{"simplestSIMPLE", { "a", "r", "such", "pattern", "aPlus", "d" }},
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarToProcRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<std::string>> res = modifiesStore.getVarToProcRelationship();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedSet = {
				{"a", { "simplestSIMPLE" }},
				{"r", { "simplestSIMPLE" }},
				{"such", { "simplestSIMPLE" }},
				{"pattern", { "simplestSIMPLE" }},
				{"aPlus", { "simplestSIMPLE" }},
				{"d", { "simplestSIMPLE" }},
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByProc() positive query") {
			std::unordered_set<std::string> res = modifiesStore.getVarByProc("simplestSIMPLE");
			std::unordered_set<std::string> expectedSet = { "a", "r", "such", "pattern", "aPlus", "d" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByProc() negative query - invalid proc name") {
			std::unordered_set<std::string> res = modifiesStore.getVarByProc("rarara");
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcByVar() positive query") {
			std::unordered_set<std::string> res = modifiesStore.getProcByVar("such");
			std::unordered_set<std::string> expectedSet = { "simplestSIMPLE" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcByVar() negative query - invalid var name") {
			std::unordered_set<std::string> res = modifiesStore.getProcByVar("rerere");
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcToVarByProcs() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = modifiesStore.getProcToVarByProcs({"simplestSIMPLE"});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("a");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("r");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("such");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("pattern");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("aPlus");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("d");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		SECTION("getProcToVarByProcs() negative query - empty set of procs") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = modifiesStore.getProcToVarByProcs({});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = {};

			REQUIRE(set == expectedSet);
		}

		SECTION("getProcToVarByProcs() negative query - invalid proc name") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = modifiesStore.getProcToVarByProcs({"faakeproc"});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = {};

			REQUIRE(set == expectedSet);
		}
	}
	modifiesStore.clear();
}
