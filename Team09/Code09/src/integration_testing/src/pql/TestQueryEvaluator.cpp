#include "catch.hpp"
#include "pkb/PKB.h"
#include "models/QueryArgument.h"
#include "models/QueryClause.h"
#include "models/Query.h"
#include "PQL/QueryEvaluator.h"
#include "PQL/QueryResultProjector.h"

TEST_CASE("QueryEvaluator evaluate normal synonym queries") {

	SECTION("no clauses") {
		PKB::clearAllStores();

		PKB::addReadStatement(3, "r");
		PKB::addReadStatement(4, "r");

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

		PKB::addPrintStatement(1, "p");
		PKB::addPrintStatement(2, "p");
		PKB::addPrintStatement(3, "p");
		PKB::addPrintStatement(4, "p");

		PKB::addAssignStatement(5, "x", "y");
		PKB::addAssignStatement(6, "x", "x y +");

		std::vector<QueryArgument> selectSynonyms = {{"pn", EntityType::PRINT}};

		std::vector<QueryArgument> clauseArguments = {
			{"x",   EntityType::STRING},
			{"_x_", EntityType::STRING},
		};
		std::unordered_set<std::string> usedSynonyms = {"a"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, clauseArguments, usedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, clauseArguments, usedSynonyms, "a");

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

		std::unordered_set<std::string> controlVariables = {"v"};
		PKB::addIfStatement(4, controlVariables);
		PKB::addIfStatement(9, controlVariables);

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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

		std::unordered_set<std::string> controlVariables = {"v"};
		PKB::addIfStatement(1, controlVariables);
		PKB::addIfStatement(8, controlVariables);
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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

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
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryClause> clauses = {stClause, pAClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"a", {"1", "3", "4"}}, {"v", {"y", "x", "y"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("multi clause - single group - single select synonym") {
		PKB::clearAllStores();
		/*
		 * assign a; procedure p; stmt s;
		 * select a such that Calls(p,_) pattern a(v,_) such that Uses (p,v)
		 */

		PKB::addProcedure("proc1");
		PKB::addProcedure("proc2");
		PKB::addCalls("proc1", "proc2");
		PKB::addAssignStatement(2, "x", "x 1 +");
		PKB::addAssignStatement(3, "y", "y x +");
		PKB::addAssignStatement(4, "z", "y x +");
		PKB::addUsesProcedure("proc1", {"x", "y"});

		std::vector<QueryArgument> callsClauseArguments = {
			{"p", EntityType::PROC},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> callsUsedSynonyms = {"p"};
		QueryClause callsClause = QueryClause(RelationRef::CALLS, callsClauseArguments, callsUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v", EntityType::VAR},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a",
														  "v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryArgument> usesClauseArguments = {
			{"p", EntityType::PROC},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> usesUsedSynonyms = {"p",
															"v"};
		QueryClause usesClause = QueryClause(RelationRef::USES, usesClauseArguments, usesUsedSynonyms);

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN}};
		std::vector<QueryClause> clauses = {callsClause, pAClause, usesClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{{"p", {"proc1", "proc1"}}, {"v", {"x", "y"}}, {"a", {"2", "3"}}}};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("multi clause groups - multi select synonym, 1 not in clauses") {
		PKB::clearAllStores();
		/*
		 * assign a; procedure p; stmt s;
		 * select <a, p> such that Uses(s,_) pattern a(v,_) such that Modifies (a,v)
		 */

		PKB::addProcedure("proc1");
		PKB::addProcedure("proc2");
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);
		PKB::addStatementNumber(4);
		PKB::addUsesStatement(2, {"x"});
		PKB::addUsesStatement(3, {"y", "x"});
		PKB::addUsesStatement(4, {"y", "x"});
		PKB::addAssignStatement(2, "x", "x 1 +");
		PKB::addAssignStatement(3, "y", "y x +");
		PKB::addAssignStatement(4, "z", "y x +");
		PKB::addModifiesStatement(2, {"x"});
		PKB::addModifiesStatement(3, {"y"});
		PKB::addModifiesStatement(4, {"z"});

		std::vector<QueryArgument> usesClauseArguments = {
			{"s", EntityType::STMT},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> usesUsedSynonyms = {"s"};
		QueryClause usesClause = QueryClause(RelationRef::USES, usesClauseArguments, usesUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v", EntityType::VAR},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryArgument> modifiesClauseArguments = {
			{"a", EntityType::ASSIGN},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> modifiesUsedSynonyms = {"a", "v"};
		QueryClause modifiesClause = QueryClause(RelationRef::MODIFIES, modifiesClauseArguments, modifiesUsedSynonyms);

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN},
													 {"p", EntityType::PROC}};
		std::vector<QueryClause> clauses = {usesClause, pAClause, modifiesClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{
										  {"p", {"proc1", "proc1", "proc1", "proc2", "proc2", "proc2"}},
										  {"v", {"x", "y", "z", "x", "y", "z"}},
										  {"a", {"2", "3", "4", "2", "3", "4"}}
									  }};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	SECTION("multi clause groups - multi select synonym") {
		PKB::clearAllStores();
		/*
		 * assign a; stmt s;
		 * select <a, s> such that Uses(s,_) pattern a(v,_) such that Modifies (a,v)
		 */

		PKB::addStatementNumber(2);
		PKB::addStatementNumber(3);
		PKB::addStatementNumber(4);
		PKB::addUsesStatement(2, {"x"});
		PKB::addUsesStatement(3, {"y", "x"});
		PKB::addUsesStatement(4, {"y", "x"});
		PKB::addAssignStatement(2, "x", "x 1 +");
		PKB::addAssignStatement(3, "y", "y x +");
		PKB::addAssignStatement(4, "z", "y x +");
		PKB::addModifiesStatement(2, {"x"});
		PKB::addModifiesStatement(3, {"y"});
		PKB::addModifiesStatement(4, {"z"});

		std::vector<QueryArgument> usesClauseArguments = {
			{"s", EntityType::STMT},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> usesUsedSynonyms = {"s"};
		QueryClause usesClause = QueryClause(RelationRef::USES, usesClauseArguments, usesUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v", EntityType::VAR},
			{"_", EntityType::WILD}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_ASSIGN, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryArgument> modifiesClauseArguments = {
			{"a", EntityType::ASSIGN},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> modifiesUsedSynonyms = {"a", "v"};
		QueryClause modifiesClause = QueryClause(RelationRef::MODIFIES, modifiesClauseArguments, modifiesUsedSynonyms);

		std::vector<QueryArgument> selectSynonyms = {{"a", EntityType::ASSIGN},
													 {"s", EntityType::STMT}};
		std::vector<QueryClause> clauses = {usesClause, pAClause, modifiesClause};
		Query query = Query(selectSynonyms, clauses, false);

		QueryClauseResult expected = {{
										  {"s", {"2", "2", "2", "3", "3", "3", "4", "4", "4"}},
										  {"v", {"x", "y", "z", "x", "y", "z", "x", "y", "z"}},
										  {"a", {"2", "3", "4", "2", "3", "4", "2", "3", "4"}}
									  }};
		QueryClauseResult actual = {QueryEvaluator::evaluate(query)};

		REQUIRE(actual == expected);
	}

	PKB::clearAllStores();
}

TEST_CASE("QueryEvaluator evaluate boolean queries") {
	SECTION("Query evaluate to false") {
		PKB::clearAllStores();
		/*
		 * assign a; stmt s; variable v; procedure p; call c;
		 * Select BOOLEAN such that Uses (p, v) pattern a(v, ”a1”) such that Modifies (s, “a2”) and Parent(5, 6)
		 */
		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(5);
		PKB::addStatementNumber(6);

		PKB::addProcedure("proc1");
		PKB::addProcedure("proc2");
		PKB::addUsesProcedure("proc2", {"x", "y", "z"});
		PKB::addUsesProcedure("proc1", {"a", "b", "c"});

		PKB::addModifiesStatement(1, {"a1"});
		PKB::addModifiesStatement(2, {"a2"});

		PKB::addAssignStatement(1, "a1", "x y +");
		PKB::addAssignStatement(2, "a2", "y z +");
		PKB::addParent(5, 6);

		std::vector<QueryArgument> usesClauseArguments = {
			{"p", EntityType::PROC},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> usesUsedSynonyms = {"p", "v"};
		QueryClause usesClause = QueryClause(RelationRef::USES, usesClauseArguments, usesUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v",  EntityType::VAR},
			{"a1", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a", "v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms);

		std::vector<QueryArgument> modifiesClauseArguments = {
			{"s",  EntityType::STMT},
			{"a2", EntityType::STRING}
		};
		std::unordered_set<std::string> modifiesUsedSynonyms = {"s"};
		QueryClause modifiesClause = QueryClause(RelationRef::MODIFIES, modifiesClauseArguments, modifiesUsedSynonyms);

		std::vector<QueryArgument> parentClauseArguments = {
			{"5", EntityType::INT},
			{"6", EntityType::INT}
		};
		std::unordered_set<std::string> parentUsedSynonyms = {};
		QueryClause parentClause = QueryClause(RelationRef::PARENT, parentClauseArguments, parentUsedSynonyms);

		std::vector<QueryArgument> selectSynonyms = {};
		std::vector<QueryClause> clauses = {usesClause, pAClause, modifiesClause, parentClause};
		Query query = Query(selectSynonyms, clauses, true);

		std::unordered_set<std::string> expected = {"FALSE"};

		Table actual = QueryEvaluator::evaluate(query);
		std::unordered_set<std::string> actualString = QueryResultProjector::formatResult(actual, query);

		REQUIRE(actualString == expected);
	}

	SECTION("Query evaluate to true") {
		PKB::clearAllStores();
		/*
		 * assign a; stmt s; variable v; procedure p;
		 * Select BOOLEAN such that Uses (p, v) pattern a(v, ”a1”) such that Modifies (s, “a2”) and Parent(5, 6)
		 */
		PKB::addStatementNumber(1);
		PKB::addStatementNumber(2);
		PKB::addStatementNumber(5);
		PKB::addStatementNumber(6);

		PKB::addProcedure("proc1");
		PKB::addProcedure("proc2");
		PKB::addUsesProcedure("proc2", {"a1", "a2", "a3"});
		PKB::addUsesProcedure("proc1", {"a", "b", "c"});

		PKB::addModifiesStatement(1, {"a1"});
		PKB::addModifiesStatement(2, {"a2"});

		PKB::addAssignStatement(1, "a1", "a2 c3 +");
		PKB::addAssignStatement(2, "a2", "a1");
		PKB::addParent(5, 6);

		std::vector<QueryArgument> usesClauseArguments = {
			{"p", EntityType::PROC},
			{"v", EntityType::VAR}
		};
		std::unordered_set<std::string> usesUsedSynonyms = {"p", "v"};
		QueryClause usesClause = QueryClause(RelationRef::USES, usesClauseArguments, usesUsedSynonyms);

		std::vector<QueryArgument> pAClauseArguments = {
			{"v",  EntityType::VAR},
			{"a1", EntityType::STRING}
		};
		std::unordered_set<std::string> pAUsedSynonyms = {"a", "v"};
		QueryClause pAClause = QueryClause(RelationRef::PATTERN_A, pAClauseArguments, pAUsedSynonyms, "a");

		std::vector<QueryArgument> modifiesClauseArguments = {
			{"s",  EntityType::STMT},
			{"a2", EntityType::STRING}
		};
		std::unordered_set<std::string> modifiesUsedSynonyms = {"s"};
		QueryClause modifiesClause = QueryClause(RelationRef::MODIFIES, modifiesClauseArguments, modifiesUsedSynonyms);

		std::vector<QueryArgument> parentClauseArguments = {
			{"5", EntityType::INT},
			{"6", EntityType::INT}
		};
		std::unordered_set<std::string> parentUsedSynonyms = {};
		QueryClause parentClause = QueryClause(RelationRef::PARENT, parentClauseArguments, parentUsedSynonyms);

		std::vector<QueryArgument> selectSynonyms = {};
		std::vector<QueryClause> clauses = {usesClause, pAClause, modifiesClause, parentClause};
		Query query = Query(selectSynonyms, clauses, true);

		std::unordered_set<std::string> expected = {"TRUE"};

		Table actual = QueryEvaluator::evaluate(query);
		std::unordered_set<std::string> actualString = QueryResultProjector::formatResult(actual, query);

		REQUIRE(actualString == expected);
	}

	PKB::clearAllStores();
}
