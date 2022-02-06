#include "catch.hpp"
#include "pkb/PKB.h"
#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "PQL/QueryEvaluator.h"

TEST_CASE("QueryEvaluator evaluate") {
	PKB::clearAllStores();

	SECTION("Initialise PKB data") {
		PKB::addProcedure("test1");
		PKB::addProcedure("test2");

		PKB::addVariable("a");
		PKB::addVariable("b");
		PKB::addVariable("c");
		PKB::addVariable("d");

		PKB::addConstant("97");
		PKB::addConstant("98");

		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);
		PKB::addStatementNumber(4);

		PKB::addAssignStatement(1, "a", "a 97 +");
		PKB::addAssignStatement(2, "b", "a c * 98 +");

		PKB::addStatementWithType(EntityType::READ, 3);
		PKB::addStatementWithType(EntityType::READ, 4);

		PKB::addModifiesStatement(1, {"a"});
		PKB::addModifiesStatement(2, {"b"});

		PKB::addUsesStatement(1, {"a"});
		PKB::addUsesStatement(2, {"a", "c"});

		SECTION("evaluate no clauses returns table corresponding to synonym type") {
			std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::READ}};
			std::vector<QueryClause> clauses;
			Query query = Query(selectSynonyms, clauses);

			QueryClauseTable expected = {{{"s", {"3", "4"}}}};
			QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

			REQUIRE(actual == expected);
		}

		SECTION("evaluate one such that clause no select synonym returns table corresponding to synonym type") {
			std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::STMT}};

			std::vector<QueryArgument> clauseArguments = {
				{"s1", EntityType::STMT},
				{"a",  EntityType::STRING}
			};
			std::unordered_set<std::string> usedSynonyms = {"s1", "a"};
			QueryClause clause = QueryClause(RelationRef::MODIFIES, clauseArguments, usedSynonyms);

			std::vector<QueryClause> clauses = {clause};
			Query query = Query(selectSynonyms, clauses);

			QueryClauseTable expected = {{{"s", {"1", "2", "3", "4"}}}};
			QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

			REQUIRE(actual == expected);
		}

		SECTION("evaluate one such that clause one select synonym returns table projection from clause result") {
			std::vector<QueryArgument> selectSynonyms = {{"v", EntityType::VAR}};

			std::vector<QueryArgument> clauseArguments = {
				{"s", EntityType::STMT},
				{"v", EntityType::VAR}
			};
			std::unordered_set<std::string> usedSynonyms = {"s", "v"};
			QueryClause clause = QueryClause(RelationRef::USES, clauseArguments, usedSynonyms);

			std::vector<QueryClause> clauses = {clause};
			Query query = Query(selectSynonyms, clauses);

			QueryClauseTable expected = {{{"s", {"1", "2", "2"}}, {"v", {"a", "a", "c"}}}};
			QueryClauseTable actual = {QueryEvaluator::evaluate(query)};

			REQUIRE(actual == expected);
		}
	}
}
