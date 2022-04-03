#include "catch.hpp"

#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "models/optimizer/OptimizerGroup.h"
#include "PQL/Optimizer.h"
#include "PQL/WeightEstimator.h"

TEST_CASE("Test optimizer extraction logic") {
	// Clauses without select synonyms
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

	// Clauses with select synonyms
	std::vector<QueryArgument> args6 = {{"p", EntityType::PROC},
										{"v", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn6 = {"p",
												"v"};
	QueryClause clause6 = {RelationRef::MODIFIES, args6, usedSyn6};

	std::vector<QueryArgument> args7 = {{"p",  EntityType::STMT},
										{"v2", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn7 = {"p",
												"v2"};
	QueryClause clause7 = {RelationRef::USES, args7, usedSyn7};

	std::vector<QueryArgument> args8 = {{"_", EntityType::WILD},
										{"_", EntityType::WILD}};
	std::unordered_set<std::string> usedSyn8 = {"a"};
	QueryClause clause8 = {RelationRef::PATTERN_ASSIGN, args8, usedSyn8, "a"};

	// Clauses without synonyms
	std::vector<QueryArgument> args9 = {{"1", EntityType::INT},
										{"y", EntityType::VAR}};
	std::unordered_set<std::string> usedSyn9 = {};
	QueryClause clause9 = {RelationRef::USES, args9, usedSyn9};

	std::vector<QueryArgument> resultSyns = {
		{"p", EntityType::PROC},
		{"a", EntityType::ASSIGN},
		{"s", EntityType::STMT}
	};
	std::vector<QueryClause> clauses = {
		clause1,
		clause2,
		clause3,
		clause4,
		clause5,
		clause6,
		clause7,
		clause8,
		clause9
	};
	Query query = {resultSyns, clauses, false};

	std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual> actualSynNotInClauses;
	std::unordered_set<QueryArgument, std::hash<QueryArgument>> actualSynWithRef;
	std::vector<QueryClause> actualClausesWithoutSyn;
	std::vector<OptimizerGroup> actualGroupClauses;

	std::tie(actualSynNotInClauses, actualSynWithRef, actualClausesWithoutSyn,
			 actualGroupClauses) = Optimizer::optimize(
		query);

	OptimizerGroup group1 = OptimizerGroup();
	group1.addEdge(clause6, WeightEstimator::estimateWeight(clause6));
	group1.addEdge(clause7, WeightEstimator::estimateWeight(clause7));
	OptimizerGroup group2 = OptimizerGroup();
	group2.addEdge(clause8, WeightEstimator::estimateWeight(clause8));
	OptimizerGroup group3 = OptimizerGroup();
	group3.addEdge(clause1, WeightEstimator::estimateWeight(clause1));
	group3.addEdge(clause2, WeightEstimator::estimateWeight(clause2));
	group3.addEdge(clause3, WeightEstimator::estimateWeight(clause3));
	group3.addEdge(clause4, WeightEstimator::estimateWeight(clause4));
	group3.addEdge(clause5, WeightEstimator::estimateWeight(clause5));

	std::unordered_set<QueryArgument, std::hash<QueryArgument>, QueryArgumentSetEqual> expectedSynNotInClauses = {
		{"s", EntityType::STMT}};
	std::vector<QueryClause> expectedClausesWithoutSyn = {clause9};
	std::vector<OptimizerGroup> expectedGroupClauses = {group2, group1, group3};

	REQUIRE(actualSynNotInClauses == expectedSynNotInClauses);
	REQUIRE(actualSynWithRef.empty());
	REQUIRE(actualClausesWithoutSyn == expectedClausesWithoutSyn);
	REQUIRE(actualGroupClauses == expectedGroupClauses);
}
