#include "catch.hpp"
#include "models/QueryClause.h"
#include "models/OptimizerGroup.h"

TEST_CASE("Test correctness of adjacency list building") {
	OptimizerGroup query;

	std::vector<QueryArgument> args1 = {{"1", EntityType::INT},
										{"x", EntityType::STRING}};
	std::unordered_set<std::string> usedSyn1 = {};
	QueryClause clause1 = {RelationRef::MODIFIES, args1, usedSyn1};

	REQUIRE_FALSE(query.addEdge(clause1, 0));
	REQUIRE(query.getAdjList().empty());

	std::vector<QueryArgument> args2 = {{"s", EntityType::STMT},
										{"x", EntityType::STRING}};
	std::unordered_set<std::string> usedSyn2 = {"s"};
	QueryClause clause2 = {RelationRef::MODIFIES, args2, usedSyn2};

	REQUIRE(query.addEdge(clause2, 0));

	std::vector<QueryArgument> args3 = {{"s", EntityType::STMT},
										{"v", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn3 = {"s", "v"};
	QueryClause clause3 = {RelationRef::MODIFIES, args3, usedSyn3};

	REQUIRE(query.addEdge(clause3, 0));

	std::vector<QueryArgument> args4 = {{"s1", EntityType::STMT},
										{"v1", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn4 = {"s1", "v1"};
	QueryClause clause4 = {RelationRef::MODIFIES, args4, usedSyn4};

	REQUIRE(query.addEdge(clause4, 0));

	std::unordered_map<std::string, std::vector<OptimizerClause>> expected = {
		{"s",  {{"s",  "s",  0, clause2}, {"s", "v", 0, clause3}}},
		{"v",  {{"v",  "s",  0, clause3}}},
		{"s1", {{"s1", "v1", 0, clause4}}},
		{"v1", {{"v1", "s1", 0, clause4}}}
	};
	std::unordered_map<std::string, std::vector<OptimizerClause>> actual = query.getAdjList();

	REQUIRE(actual == expected);
}
