#include "catch.hpp"
#include "pkb/stores/UsesStore.h"

TEST_CASE("UsesStore API") {
	UsesStore usesStore;
	usesStore.clear();

	// Populating PKB information based on simplestSIMPLE.txt
	SECTION("Initialization of program variables") {
		usesStore.addStmtVarRelationship(1, { "a", "b", "c", "d" });
		usesStore.addStmtVarRelationship(3, { "pn" });
		usesStore.addStmtVarRelationship(4, { "true" });
		usesStore.addStmtVarRelationship(5, { "that", "team9" });
		usesStore.addStmtVarRelationship(6, { "nice" });
		usesStore.addStmtVarRelationship(7, { "a", "false" });
		usesStore.addStmtVarRelationship(8, { "true" });
		usesStore.addStmtVarRelationship(9, { "c" });
		usesStore.addProcVarRelationship("simplestSIMPLE", { "a", "b", "c", "d", "pn", "true", "that", "team9", "nice", "false" });

		// --------------------------------------------------
		//                  Getters
		// --------------------------------------------------

		SECTION("getStmtInRelationship() positive query") {
			std::unordered_set<int> res = usesStore.getStmtInRelationship();
			std::unordered_set<int> expectedSet = { 1, 3, 4, 5, 6, 7, 8, 9 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarInRelationship() positive query") {
			std::unordered_set<std::string> res = usesStore.getVarInRelationship();
			std::unordered_set<std::string> expectedSet = { "a", "b", "c", "d", "pn", "true", "that", "team9", "nice", "false" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getStmtToVarRelationship() positive query") {
			std::unordered_map<int, std::unordered_set<std::string>> res = usesStore.getStmtToVarRelationship();
			std::unordered_map<int, std::unordered_set<std::string>> expectedSet = {
				{1, { "a", "b", "c", "d" }},
				{3, { "pn" }},
				{4, { "true" }},
				{5, { "that", "team9" }},
				{6, { "nice" }},
				{7, { "a", "false" }},
				{8, { "true" }},
				{9, { "c" }}
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarToStmtRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<int>> res = usesStore.getVarToStmtRelationship();
			std::unordered_map<std::string, std::unordered_set<int>> expectedSet = {
				{"a", { 1, 7 }},
				{"b", { 1 }},
				{"c", { 1, 9 }},
				{"d", { 1 }},
				{"pn", { 3 }},
				{"true", { 4, 8 }},
				{"that", { 5 }},
				{"team9", { 5 }},
				{"nice", { 6 }},
				{"false", { 7 }}
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByStmt() positive query") {
			std::unordered_set<std::string> res = usesStore.getVarByStmt(7);
			std::unordered_set<std::string> expectedSet = { "a", "false" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByStmt() negative query - invalid statement number") {
			std::unordered_set<std::string> res = usesStore.getVarByStmt(10);
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}

		SECTION("getStmtByVar() positive query") {
			std::unordered_set<int> res = usesStore.getStmtByVar("a");
			std::unordered_set<int> expectedSet = { 1, 7 };
			REQUIRE(res == expectedSet);
		}

		SECTION("getStmtToVarByStmts() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = usesStore.getStmtToVarByStmts({ 7, 8, 9 });
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("7");
			secondColumn.push_back("a");
			firstColumn.push_back("7");
			secondColumn.push_back("false");
			firstColumn.push_back("8");
			secondColumn.push_back("true");
			firstColumn.push_back("9");
			secondColumn.push_back("c");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		SECTION("getStmtToVarByStmts() negative query with invalid statement numbers") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = usesStore.getStmtToVarByStmts({ 1, 2, 3, 10, 11, 12 });
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("1");
			secondColumn.push_back("a");
			firstColumn.push_back("1");
			secondColumn.push_back("b");
			firstColumn.push_back("1");
			secondColumn.push_back("c");
			firstColumn.push_back("1");
			secondColumn.push_back("d");
			firstColumn.push_back("3");
			secondColumn.push_back("pn");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		SECTION("getProcInRelationship() positive query") {
			std::unordered_set<std::string> res = usesStore.getProcInRelationship();
			std::unordered_set<std::string> expectedSet = { "simplestSIMPLE" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcToVarRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<std::string>> res = usesStore.getProcToVarRelationship();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedSet = {
				{"simplestSIMPLE", { "a", "b", "c", "d", "pn", "true", "that", "team9", "nice", "false"}},
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarToProcRelationship() positive query") {
			std::unordered_map<std::string, std::unordered_set<std::string>> res = usesStore.getVarToProcRelationship();
			std::unordered_map<std::string, std::unordered_set<std::string>> expectedSet = {
				{"a", { "simplestSIMPLE" }},
				{"b", { "simplestSIMPLE" }},
				{"c", { "simplestSIMPLE" }},
				{"d", { "simplestSIMPLE" }},
				{"pn", { "simplestSIMPLE" }},
				{"true", { "simplestSIMPLE" }},
				{"that", { "simplestSIMPLE" }},
				{"team9", { "simplestSIMPLE" }},
				{"nice", { "simplestSIMPLE" }},
				{"false", { "simplestSIMPLE" }}
			};
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByProc() positive query") {
			std::unordered_set<std::string> res = usesStore.getVarByProc("simplestSIMPLE");
			std::unordered_set<std::string> expectedSet = { "a", "b", "c", "d", "pn", "true", "that", "team9", "nice", "false" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getVarByProc() negative query - invalid proc name") {
			std::unordered_set<std::string> res = usesStore.getVarByProc("lalala");
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcByVar() positive query") {
			std::unordered_set<std::string> res = usesStore.getProcByVar("team9");
			std::unordered_set<std::string> expectedSet = { "simplestSIMPLE" };
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcByVar() negative query - invalid var name") {
			std::unordered_set<std::string> res = usesStore.getProcByVar("lelele");
			std::unordered_set<std::string> expectedSet = {};
			REQUIRE(res == expectedSet);
		}

		SECTION("getProcToVarByProcs() positive query") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = usesStore.getProcToVarByProcs({"simplestSIMPLE"});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("a");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("b");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("c");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("d");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("pn");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("true");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("that");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("team9");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("nice");
			firstColumn.push_back("simplestSIMPLE");
			secondColumn.push_back("false");

			std::tuple<std::vector<std::string>, std::vector<std::string>> expectedRes = { firstColumn, secondColumn };

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(expectedRes), std::get<1>(expectedRes));

			REQUIRE(set == expectedSet);
		}

		SECTION("getProcToVarByProcs() negative query - empty set of procs") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = usesStore.getProcToVarByProcs({});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = {};

			REQUIRE(set == expectedSet);
		}

		SECTION("getProcToVarByProcs() negative query - invalid proc name") {
			std::tuple<std::vector<std::string>, std::vector<std::string>> res = usesStore.getProcToVarByProcs({"fakeproc"});
			std::vector<std::string> firstColumn;
			std::vector<std::string> secondColumn;

			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> set =
				PKBUtil::convertVectorTupleToSetPairs(std::get<0>(res), std::get<1>(res));
			std::unordered_set<std::pair<std::string, std::string>, PKBUtil::pairHashFunction> expectedSet = {};

			REQUIRE(set == expectedSet);
		}
	}
	usesStore.clear();
}
