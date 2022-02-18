#include "catch.hpp"
#include "pkb/PKB.h"
#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "PQL/QueryEvaluator.h"

TEST_CASE("QueryEvaluator evaluate") {
	SECTION("evaluate no clauses returns table corresponding to synonym type") {
		PKB::clearAllStores();

		PKB::addStatementWithType(EntityType::READ, 3);
		PKB::addStatementWithType(EntityType::READ, 4);

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::READ}};
		std::vector<QueryClause> clauses;
		Query query = Query(selectSynonyms, clauses);

		QueryClauseTable expected = {{{"s", {"3", "4"}}}};
		QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("evaluate one st clause don't contain select returns table corresponding to synonym type") {
		PKB::clearAllStores();

		PKB::addModifiesStatement(1, { "a" });
		PKB::addModifiesStatement(2, { "a" });
		PKB::addModifiesStatement(3, { "a" });
		PKB::addModifiesStatement(4, { "a" });

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::STMT}};

		std::vector<QueryArgument> clauseArguments = {
			{"s1", EntityType::STMT},
			{"a",  EntityType::STRING}
		};
		std::unordered_set<std::string> usedSynonyms = {"s1", "a"};
		QueryClause stClause = QueryClause(RelationRef::MODIFIES, clauseArguments, usedSynonyms);

		std::vector<QueryClause> clauses = {stClause};
		Query query = Query(selectSynonyms, clauses);

		QueryClauseTable expected = {{{"s", {"1", "2", "3", "4"}}}};
		QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("evaluate one st clause contains select returns table projection from clause result") {
		PKB::clearAllStores();
		
		PKB::addUsesStatement(1, { "a" });
		PKB::addUsesStatement(2, { "a", "c" });

		std::vector<QueryArgument> selectSynonyms = {{"v", EntityType::VAR}};

		std::vector<QueryArgument> clauseArguments = {
			{"s", EntityType::STMT},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> usedSynonyms = {"s", "v"};
		QueryClause stClause = QueryClause(RelationRef::USES, clauseArguments, usedSynonyms);

		std::vector<QueryClause> clauses = {stClause};
		Query query = Query(selectSynonyms, clauses);

		QueryClauseTable expected = {{{"s", {"1", "2", "2"}}, {"v", {"a", "a", "c"}}}};
		QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("evaluate one pattern clause don't contain select returns table corresponding to synonym type") {
		PKB::clearAllStores();
	
		PKB::addStatementWithType(EntityType::PRINT, 1);
		PKB::addStatementWithType(EntityType::PRINT, 2);
		PKB::addStatementWithType(EntityType::PRINT, 3);
		PKB::addStatementWithType(EntityType::PRINT, 4);

		std::vector<QueryArgument> selectSynonyms = {{"pn", EntityType::PRINT}};

		std::vector<QueryArgument> clauseArguments = {
			{"x", EntityType::STRING},
			{"_x_", EntityType::STRING},
		};
		std::unordered_set<std::string> usedSynonyms = { "a" };
		QueryClause pAClause = QueryClause(RelationRef::PATTERN, clauseArguments, usedSynonyms, "a");
	
		std::vector<QueryClause> clauses = { pAClause };
		Query query = Query(selectSynonyms, clauses);

		QueryClauseTable expected = { {{"pn", {"1", "2", "3", "4"}}} };
		QueryClauseTable actual = { QueryEvaluator::evaluate(query) };

		REQUIRE(actual == expected);
	}

	SECTION("evaluate one pattern clause contains select returns table corresponding to synonym") {
		PKB::clearAllStores();

		PKB::addAssignStatement(1, "x", "x 2 +");
		PKB::addAssignStatement(2, "y", "y 2 * x 2 + +");
		PKB::addAssignStatement(3, "x", "y z +");

		std::vector<QueryArgument> selectSynonyms = { {"a", EntityType::ASSIGN} };

		std::vector<QueryArgument> clauseArguments = {
			{"x", EntityType::STRING},
			{"_x 2 +_", EntityType::STRING}
		};

		std::unordered_set<std::string> usedSynonyms = { "a" };
		QueryClause pAClause = QueryClause(RelationRef::PATTERN, clauseArguments, usedSynonyms, "a");
	
		std::vector<QueryClause> clauses = { pAClause };
		Query query = Query(selectSynonyms, clauses);

		QueryClauseTable expected = { {{"a", {"1", "2"}}} };
		QueryClauseTable actual = { QueryEvaluator::evaluate(query) };

		REQUIRE(actual == expected);
	}
}
