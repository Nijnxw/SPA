#include "catch.hpp"
#include "models/optimizer/OptimizerQuery.h"

TEST_CASE("Group empty adjacency list - should return empty") {
	OptimizerQuery query;

	std::vector<OptimizerGroup> res = query.groupClauses();
	REQUIRE(res.empty());
}

TEST_CASE("Separate single group of connected clauses - should return single optimizer group") {
	std::vector<QueryArgument> args1 = {{"s", EntityType::STMT},
										{"v", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn1 = {"s", "v"};
	QueryClause clause1 = {RelationRef::MODIFIES, args1, usedSyn1};

	std::vector<QueryArgument> args2 = {{"s", EntityType::STMT},
										{"c", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn2 = {"s", "c"};
	QueryClause clause2 = {RelationRef::MODIFIES, args2, usedSyn2};

	OptimizerGroup expected = {{
								   {"s", {{"s", "v", 0, clause1}, {"s", "c", 0, clause2}}},
								   {"v", {{"v", "s", 0, clause1}}},
								   {"c", {{"c", "s", 0, clause2}}}
							   }};

	OptimizerQuery query;
	REQUIRE(query.addEdge(clause1, 0));
	REQUIRE(query.addEdge(clause2, 0));

	auto actual = query.groupClauses();
	REQUIRE(actual.size() == 1);
	REQUIRE(actual.front() == expected);
}

TEST_CASE("Separate multiple groups of connected clauses - should return multiple optimizer groups") {
	std::vector<QueryArgument> args1 = {{"ifs", EntityType::IF},
										{"s1",  EntityType::STMT}};
	std::unordered_set<std::string> usedSyn1 = {"ifs", "s1"};
	QueryClause clause1 = {RelationRef::PARENT_T, args1, usedSyn1};

	std::vector<QueryArgument> args2 = {{"s1", EntityType::STMT},
										{"pn", EntityType::PRINT}};
	std::unordered_set<std::string> usedSyn2 = {"s1", "pn"};
	QueryClause clause2 = {RelationRef::PARENT, args2, usedSyn2};

	std::vector<QueryArgument> args3 = {{"s1", EntityType::STMT},
										{"pn", EntityType::PRINT}};
	std::unordered_set<std::string> usedSyn3 = {"s1", "pn"};
	QueryClause clause3 = {RelationRef::FOLLOWS, args3, usedSyn3};

	std::vector<QueryArgument> args4 = {{"pn", EntityType::PRINT},
										{"v1", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn4 = {"pn", "v1"};
	QueryClause clause4 = {RelationRef::USES, args4, usedSyn4};

	std::vector<QueryArgument> args5 = {{"s1", EntityType::STMT},
										{"v1", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn5 = {"s1", "v1"};
	QueryClause clause5 = {RelationRef::MODIFIES, args5, usedSyn5};

	std::vector<QueryArgument> args6 = {{"_", EntityType::WILD},
										{"_", EntityType::WILD}};
	std::unordered_set<std::string> usedSyn6 = {"a"};
	QueryClause clause6 = {RelationRef::PATTERN_ASSIGN, args6, usedSyn6, "a"};

	OptimizerGroup expected1 = {{
									{"ifs", {{"ifs", "s1", 0, clause1}}},
									{"s1",
									 {{"s1", "ifs", 0, clause1}, {"s1", "pn", 0, clause2}, {"s1", "pn", 0, clause3},
									  {"s1", "v1", 0, clause5}}},
									{"pn",
									 {{"pn", "s1", 0, clause2}, {"pn", "s1", 0, clause3}, {"pn", "v1", 0, clause4}}},
									{"v1", {{"v1", "pn", 0, clause4}, {"v1", "s1", 0, clause5}}},
								}};

	OptimizerGroup expected2 = {{
									{"a", {{"a", "a", 0, clause6}}}
								}};

	OptimizerQuery query;
	REQUIRE(query.addEdge(clause1, 0));
	REQUIRE(query.addEdge(clause2, 0));
	REQUIRE(query.addEdge(clause3, 0));
	REQUIRE(query.addEdge(clause4, 0));
	REQUIRE(query.addEdge(clause5, 0));
	REQUIRE(query.addEdge(clause6, 0));

	auto actual = query.groupClauses();
	REQUIRE(actual.size() == 2);
	REQUIRE(actual.front() == expected1);
	REQUIRE(actual.back() == expected2);
}
