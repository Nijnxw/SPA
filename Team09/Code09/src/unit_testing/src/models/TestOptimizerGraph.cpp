#include "catch.hpp"
#include "models/QueryClause.h"
#include "models/OptimizerGraph.h"

TEST_CASE("Add no synonym clause - should fail") {
	std::vector<QueryArgument> args = {{"1", EntityType::INT},
									   {"x", EntityType::STRING}};
	std::unordered_set<std::string> usedSyn = {};
	QueryClause clause = {RelationRef::MODIFIES, args, usedSyn};

	OptimizerGraph graph;

	REQUIRE_FALSE(graph.addEdge(clause, 0));
	REQUIRE(graph.getAdjList().empty());
}

TEST_CASE("Add single synonym - should have an edge loop back to same vertex") {
	std::vector<QueryArgument> args = {{"s", EntityType::STMT},
									   {"x", EntityType::STRING}};
	std::unordered_set<std::string> usedSyn = {"s"};
	QueryClause clause = {RelationRef::MODIFIES, args, usedSyn};

	std::unordered_map<std::string, std::vector<OptimizerClause>> expected = {
		{"s", {{"s", "s", 0, clause}}}
	};

	OptimizerGraph graph;

	REQUIRE(graph.addEdge(clause, 0));
	auto actual = graph.getAdjList();
	REQUIRE(actual == expected);
}

TEST_CASE("Add 2 synonyms (repeated) - should have an edge loop back to same vertex") {
	std::vector<QueryArgument> args = {{"s", EntityType::STMT},
									   {"s", EntityType::STMT}};
	std::unordered_set<std::string> usedSyn = {"s"};
	QueryClause clause = {RelationRef::FOLLOWS, args, usedSyn};

	std::unordered_map<std::string, std::vector<OptimizerClause>> expected = {
		{"s", {{"s", "s", 0, clause}}}
	};

	OptimizerGraph graph;

	REQUIRE(graph.addEdge(clause, 0));
	auto actual = graph.getAdjList();
	REQUIRE(actual == expected);
}

TEST_CASE("Add 2 synonyms (both different) - should have edge between 2 vertices") {
	std::vector<QueryArgument> args = {{"s", EntityType::STMT},
									   {"v", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn = {"s", "v"};
	QueryClause clause = {RelationRef::MODIFIES, args, usedSyn};

	std::unordered_map<std::string, std::vector<OptimizerClause>> expected = {
		{"s", {{"s", "v", 0, clause}}},
		{"v", {{"v", "s", 0, clause}}}
	};

	OptimizerGraph graph;

	REQUIRE(graph.addEdge(clause, 0));
	auto actual = graph.getAdjList();
	REQUIRE(actual == expected);
}
