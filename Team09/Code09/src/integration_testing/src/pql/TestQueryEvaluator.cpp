#include "catch.hpp"
#include "pkb/PKB.h"
#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "PQL/QueryEvaluator.h"

TEST_CASE("QueryEvaluator evaluate") {

	SECTION("no clauses") {
		PKB::clearAllStores();

		PKB::addStatementWithType(EntityType::READ, 3);
		PKB::addStatementWithType(EntityType::READ, 4);

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::READ}};
		std::vector<QueryClause> clauses;
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"s", {"3", "4"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that clause - don't contain select synonym") {
		PKB::clearAllStores();

		PKB::addModifiesStatement(1, {"a"});
		PKB::addModifiesStatement(2, {"a"});
		PKB::addModifiesStatement(3, {"a"});
		PKB::addModifiesStatement(4, {"a"});

		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::STMT}};

		std::vector<QueryArgument> clauseArguments = {
			{"s1", EntityType::STMT},
			{"a",  EntityType::STRING}
		};
		std::unordered_set<std::string> usedSynonyms = {"s1", "a"};
		QueryClause stClause = QueryClause(RelationRef::MODIFIES, clauseArguments, usedSynonyms);

		std::vector<QueryClause> clauses = {stClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"s", {"1", "2", "3"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that clause - contains select synonym") {
		PKB::clearAllStores();

		PKB::addUsesStatement(1, {"a"});
		PKB::addUsesStatement(2, {"a", "c"});

		std::vector<QueryArgument> selectSynonyms = {{"v", EntityType::VAR}};

		std::vector<QueryArgument> clauseArguments = {
			{"s", EntityType::STMT},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> usedSynonyms = {"s", "v"};
		QueryClause stClause = QueryClause(RelationRef::USES, clauseArguments, usedSynonyms);

		std::vector<QueryClause> clauses = {stClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"s", {"1", "2", "2"}}, {"v", {"a", "a", "c"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one pattern clause - don't contain select synonym") {
		PKB::clearAllStores();

		PKB::addStatementWithType(EntityType::PRINT, 1);
		PKB::addStatementWithType(EntityType::PRINT, 2);
		PKB::addStatementWithType(EntityType::PRINT, 3);
		PKB::addStatementWithType(EntityType::PRINT, 4);

		PKB::addAssignStatement(5, "x", "y");
		PKB::addAssignStatement(6, "x", "x y +");

		std::vector<QueryArgument> selectSynonyms = {{"pn", EntityType::PRINT}};

		std::vector<QueryArgument> clauseArguments = {
			{"x",   EntityType::STRING},
			{"_x_", EntityType::STRING},
		};
		std::unordered_set<std::string> usedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, clauseArguments, usedSynonyms, "a");

		std::vector<QueryClause> clauses = {pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"pn", {"1", "2", "3", "4"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one pattern clause - contain select synonym") {
		PKB::clearAllStores();

		PKB::addAssignStatement(1, "x", "x 2 +");
		PKB::addAssignStatement(2, "y", "y 2 * x 2 + +");
		PKB::addAssignStatement(3, "x", "y z +");

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN}};

		std::vector<QueryArgument> clauseArguments = {
			{"x",       EntityType::STRING},
			{"_x 2 +_", EntityType::STRING}
		};

		std::unordered_set<std::string> usedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, clauseArguments, usedSynonyms, "a");

		std::vector<QueryClause> clauses = {pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"a", {"1"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - no common synonyms - none contains select synonym") {
		PKB::clearAllStores();

		/*
			stmt s; assign a; if ifs;
			Select ifs such that Parent(4, s) pattern a("x", _"5"_)
		*/

		PKB::addParent(4, 5);
		PKB::addParent(4, 6);
		PKB::addParent(4, 7);
		PKB::addParent(4, 8);
		PKB::addParent(9, 10);

		PKB::addStatementWithType(EntityType::IF, 4);
		PKB::addStatementWithType(EntityType::IF, 9);

		PKB::addAssignStatement(6, "x", "5");

		std::vector<QueryArgument> selectSynonyms = {{"ifs", EntityType::IF}};

		std::vector<QueryArgument> stClauseArguments = {
			{"4", EntityType::INT},
			{"s", EntityType::STMT}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"s"};
		QueryClause stClause = QueryClause(RelationRef::PARENT, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"x",   EntityType::STRING},
			{"_5_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"ifs", {"4", "9"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - no common synonyms - such that contains select synonym") {
		PKB::clearAllStores();

		/*
			stmt s; if ifs; assign a;
			Select ifs such that Follows*(ifs, s) pattern a("y", _"y + 1"_)
		*/

		PKB::addStatementWithType(EntityType::IF, 1);
		PKB::addStatementWithType(EntityType::IF, 8);
		PKB::addFollowsT(1, 5);
		PKB::addFollowsT(1, 6);
		PKB::addFollowsT(1, 7);
		PKB::addAssignStatement(2, "y", "x 1 +");
		PKB::addAssignStatement(3, "x", "y 2 +");
		PKB::addAssignStatement(4, "y", "y 1 +");

		std::vector<QueryArgument> selectSynonyms = {{"ifs", EntityType::IF}};

		std::vector<QueryArgument> stClauseArguments = {
			{"ifs", EntityType::IF},
			{"s",   EntityType::STMT}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"ifs", "s"};
		QueryClause stClause = QueryClause(RelationRef::FOLLOWS_T, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"y",       EntityType::STRING},
			{"_y 1 +_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"ifs", {"1", "1", "1"}}, {"s", {"5", "6", "7"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - no common synonyms - pattern contains select synonym") {
		PKB::clearAllStores();

		/*
			assign a; stmt s;
			Select a such that Modifies("3", "x") pattern a("x", _"x"_)
		*/

		PKB::addModifiesStatement(1, {"y", "z"});
		PKB::addModifiesStatement(2, {"x", "y"});
		PKB::addModifiesStatement(3, {"x", "z"});

		PKB::addAssignStatement(1, "x", "y z *");
		PKB::addAssignStatement(2, "x", "x y +");
		PKB::addAssignStatement(3, "y", "x z /");

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN}};

		std::vector<QueryArgument> stClauseArguments = {
			{"3", EntityType::INT},
			{"x", EntityType::STRING}
		};
		std::unordered_set<std::string> stUsedSynonyms = {};
		QueryClause stClause = QueryClause(RelationRef::MODIFIES, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"x",   EntityType::STRING},
			{"_x_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"a", {"2"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - single common synonyms - none contain select synonym") {
		PKB::clearAllStores();

		/*
			stmt s; assign a;
			Select s such that Follows(a,2) pattern a ("x", _"x"_) 
		*/

		PKB::addFollows(1, 2);
		PKB::addAssignStatement(1, "x", "x + y");
		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::STMT}};

		std::vector<QueryArgument> stClauseArguments = {
			{"a", EntityType::ASSIGN},
			{"2", EntityType::INT}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"a"};
		QueryClause stClause = QueryClause(RelationRef::FOLLOWS, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"x",   EntityType::STRING},
			{"_x_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"s", {"1", "2", "3"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - single common synonyms - such that contains select synonym") {
		PKB::clearAllStores();

		/*
			stmt s; assign a;
			Select s such that Parent*(s,a) pattern a ("x", _"x"_)
		*/

		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);
		PKB::addStatementNumber(4);
		PKB::addStatementNumber(5);
		PKB::addStatementNumber(6);

		PKB::addAssignStatement(3, "y", "x");
		PKB::addAssignStatement(4, "x", "y x +");
		PKB::addAssignStatement(6, "x", "z x +");

		PKB::addParentT(1, 2);
		PKB::addParentT(1, 3);
		PKB::addParentT(1, 4);
		PKB::addParentT(1, 5);
		PKB::addParentT(1, 6);

		std::vector<QueryArgument> selectSynonyms = {{"s", EntityType::STMT}};

		std::vector<QueryArgument> stClauseArguments = {
			{"s", EntityType::STMT},
			{"a", EntityType::ASSIGN}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"s", "a"};
		QueryClause stClause = QueryClause(RelationRef::PARENT_T, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"x",   EntityType::STRING},
			{"_x_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"s", {"1", "1"}}, {"a", {"4", "6"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - single common synonyms - pattern contains select synonym") {
		PKB::clearAllStores();

		/*
			stmt s; assign a; variable v;
			Select a such that Uses(s,v) pattern a (v, _"x"_)
		*/

		PKB::addUsesStatement(1, {"x"});
		PKB::addUsesStatement(2, {"x", "x", "y"});
		PKB::addUsesStatement(3, {"y", "z"});
		PKB::addUsesStatement(4, {"w", "x", "y", "z"});

		PKB::addAssignStatement(1, "z", "x");
		PKB::addAssignStatement(2, "x", "y x +");
		PKB::addAssignStatement(3, "y", "z");
		PKB::addAssignStatement(4, "x", "w x * y z / +");

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN}};

		std::vector<QueryArgument> stClauseArguments = {
			{"s", EntityType::STMT},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"s", "v"};
		QueryClause stClause = QueryClause(RelationRef::USES, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v",   EntityType::VAR},
			{"_x_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a", "v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {
			{{"s", {"2", "2", "4", "4", "1", "1", "4", "3"}},
			 {"v", {"x", "x", "x", "x", "x", "x", "z", "z"}},
			 {"a", {"2", "4", "2", "4", "2", "4", "1", "1"}}
			}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("one such that one pattern clause - both common synonyms - both contains select synonym") {
		PKB::clearAllStores();

		/*
			assign a; variable v;
			Select a such that Modifies(a, v) pattern a(v, _"x"_)
		*/

		PKB::addAssignStatement(1, "y", "x");
		PKB::addAssignStatement(2, "z", "y");
		PKB::addAssignStatement(3, "x", "x");
		PKB::addAssignStatement(4, "y", "x");

		PKB::addModifiesStatement(1, {"y"});
		PKB::addModifiesStatement(2, {"z"});
		PKB::addModifiesStatement(3, {"x"});
		PKB::addModifiesStatement(4, {"y"});

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN}};

		std::vector<QueryArgument> stClauseArguments = {
			{"a", EntityType::ASSIGN},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> stUsedSynonyms = {"a", "v"};
		QueryClause stClause = QueryClause(RelationRef::MODIFIES, stClauseArguments, stUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v",   EntityType::VAR},
			{"_x_", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a", "v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"a", {"1", "3", "4"}}, {"v", {"y", "x", "y"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}
}
