#include "catch.hpp"
#include "models/QueryClauseResult.h"
#include "PQL/QueryResultProjector.h"

TEST_CASE("project single column results using no columns returns empty set") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};

	Query query({}, {}, false);
	std::unordered_set<std::string> actual = QueryResultProjector::formatResult(table, query);

	REQUIRE(actual.empty());
}

TEST_CASE("project single column results using selected columns returns set of space separated string") {
	Table table = {
		{"a", {"1", "2", "3", "4"}},
		{"b", {"5", "6", "7", "8"}}
	};

	std::vector<QueryArgument> colOrder = {
		{"a", EntityType::ASSIGN}
	};
	Query query(colOrder, {}, false);
	std::unordered_set<std::string> expected = {"1", "2", "3", "4"};
	std::unordered_set<std::string> actual = QueryResultProjector::formatResult(table, query);

	REQUIRE(actual == expected);
}

TEST_CASE("project multiple column results using selected columns returns set of space separated string") {
	Table table = {
		{"a", {"1", "2",  "3",  "4"}},
		{"b", {"5", "6",  "7",  "8"}},
		{"c", {"9", "10", "11", "12"}}
	};

	std::vector<QueryArgument> colOrder = {
		{"b", EntityType::ASSIGN},
		{"a", EntityType::VAR},
		{"c", EntityType::CALL}
	};
	Query query(colOrder, {}, false);
	std::unordered_set<std::string> expected = {"5 1 9", "6 2 10", "7 3 11", "8 4 12"};
	std::unordered_set<std::string> actual = QueryResultProjector::formatResult(table, query);

	REQUIRE(actual == expected);
}
