#include "catch.hpp"
#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/optimizer/OptimizerGroup.h"

TEST_CASE("") {
	std::vector<QueryArgument> args1 = {{"ifs", EntityType::IF},
										{"s1",  EntityType::STMT}};
	std::unordered_set<std::string> usedSyn1 = {"ifs",
												"s1"};
	QueryClause clause1 = {RelationRef::PARENT_T,
						   args1,
						   usedSyn1};

	std::vector<QueryArgument> args2 = {{"s1", EntityType::STMT},
										{"pn", EntityType::PRINT}};
	std::unordered_set<std::string> usedSyn2 = {"s1",
												"pn"};
	QueryClause clause2 = {RelationRef::PARENT,
						   args2,
						   usedSyn2};

	std::vector<QueryArgument> args3 = {{"s1", EntityType::STMT},
										{"pn", EntityType::PRINT}};
	std::unordered_set<std::string> usedSyn3 = {"s1",
												"pn"};
	QueryClause clause3 = {RelationRef::FOLLOWS,
						   args3,
						   usedSyn3};

	std::vector<QueryArgument> args4 = {{"pn", EntityType::PRINT},
										{"v1", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn4 = {"pn",
												"v1"};
	QueryClause clause4 = {RelationRef::USES,
						   args4,
						   usedSyn4};

	std::vector<QueryArgument> args5 = {{"s1", EntityType::STMT},
										{"v1", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn5 = {"s1",
												"v1"};
	QueryClause clause5 = {RelationRef::MODIFIES,
						   args5,
						   usedSyn5};

	OptimizerGroup group;

	REQUIRE(group.addEdge(clause1, 74));
	REQUIRE(group.addEdge(clause2, 12));
	REQUIRE(group.addEdge(clause3, 12));
	REQUIRE(group.addEdge(clause4, 12));
	REQUIRE(group.addEdge(clause5, 100));

	std::vector<QueryClause> expected = {clause2, clause4, clause3, clause1, clause5};
	std::vector<QueryClause> actual = group.getClauses();

	REQUIRE(actual == expected);
}
