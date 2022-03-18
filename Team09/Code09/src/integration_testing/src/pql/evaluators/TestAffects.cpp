#include "catch.hpp"
#include "PQL/evaluators/AffectsEvaluator.h"

TEST_CASE ("Test affects/*") {
	PKB::clearAllStores();

	/*
	 * procedure First {
	 * 1.	read x;
	 * 2.	read z;
	 * 3.	call Second;
	 * }
	 * procedure Second {
	 * 4.	x = 0;
	 * 5.	i = 5;
	 * 6.	while (i != 0) {
	 * 7.		x = x + 2 * y;
	 * 8.		call Third;
	 * 9. 		i = i - 1;
	 * 10.		if (i == 2) then {
	 * 11.			y = 1;
	 * 			} else {
	 * 12.			x = i;
	 * 			}
	 * 		}
	 * 13.	if (x == 1) then {
	 * 14. 		x = x + 1;
	 * 15.		z = x;
	 * 		} else {
	 * 16. 		z = 1;
	 * 		}
	 * 17.	z = z + x + i;
	 * 18.	y = z + 2;
	 * 19.	x = x * y + z;
	 * }
	 * procedure Third {
	 * 20.	z = 5;
	 * 21. 	v = z;
	 * 22.	print v;
	 * 23.	x = 6;
	 * }
	 */

	CFG cfg = {
		{},
		{2},
		{3},
		{},
		{5},
		{6},
		{7,  13},
		{8},
		{9},
		{10},
		{11, 12},
		{13},
		{13},
		{14, 16},
		{15},
		{17},
		{17},
		{18},
		{19},
		{},
		{21},
		{22},
		{23},
		{}
	};
	PKB::addCFG(cfg);

	PKB::addReadStatement(1, "x");
	PKB::addReadStatement(2, "z");
	PKB::addPrintStatement(22, "v");

	PKB::addCallStatement(3, "Second");
	PKB::addCallStatement(8, "Third");

	PKB::addWhileStatement(6, {"i"});
	PKB::addIfStatement(10, {"i"});
	PKB::addIfStatement(13, {"x"});

	PKB::addAssignStatement(4, "x", "0");
	PKB::addAssignStatement(5, "i", "5");
	PKB::addAssignStatement(7, "x", "x 2 y * +");
	PKB::addAssignStatement(9, "i", "i - 1");
	PKB::addAssignStatement(11, "y", "1");
	PKB::addAssignStatement(12, "x", "i");
	PKB::addAssignStatement(14, "x", "x 1 +");
	PKB::addAssignStatement(15, "z", "x");
	PKB::addAssignStatement(16, "z", "1");
	PKB::addAssignStatement(17, "z", "z x + i +");
	PKB::addAssignStatement(18, "y", "z 2 +");
	PKB::addAssignStatement(19, "x", "x y * z +");
	PKB::addAssignStatement(20, "z", "5");
	PKB::addAssignStatement(21, "v", "z");
	PKB::addAssignStatement(23, "x", "6");

	PKB::addModifiesProcedure("First", {"x", "z"});
	PKB::addModifiesProcedure("Second", {"i", "x", "y", "z"});
	PKB::addModifiesProcedure("Third", {"v", "z"});

	PKB::addModifiesStatement(1, {"x"});
	PKB::addModifiesStatement(2, {"z"});
	PKB::addModifiesStatement(4, {"x"});
	PKB::addModifiesStatement(5, {"i"});
	PKB::addModifiesStatement(7, {"x"});
	PKB::addModifiesStatement(9, {"i"});
	PKB::addModifiesStatement(11, {"y"});
	PKB::addModifiesStatement(12, {"x"});
	PKB::addModifiesStatement(14, {"x"});
	PKB::addModifiesStatement(15, {"z"});
	PKB::addModifiesStatement(16, {"z"});
	PKB::addModifiesStatement(17, {"z"});
	PKB::addModifiesStatement(18, {"y"});
	PKB::addModifiesStatement(19, {"x"});
	PKB::addModifiesStatement(20, {"z"});
	PKB::addModifiesStatement(21, {"v"});
	PKB::addModifiesStatement(23, {"x"});

	PKB::addUsesStatement(7, {"x", "y"});
	PKB::addUsesStatement(9, {"i"});
	PKB::addUsesStatement(14, {"x"});
	PKB::addUsesStatement(15, {"x"});
	PKB::addUsesStatement(17, {"z", "x", "i"});
	PKB::addUsesStatement(18, {"z"});
	PKB::addUsesStatement(19, {"x", "y", "z"});
	PKB::addUsesStatement(21, {"z"});
	PKB::addUsesStatement(22, {"v"});

	SECTION ("Test affects - positive cases") {
		AffectsEvaluator evaluator;
		SECTION ("LHS INT - RHS INT") {
			QueryClauseResult actual1 = evaluator.getAffects("12", "7", EntityType::INT, EntityType::INT, true);
			REQUIRE(actual1.containsValidResult());

			QueryClauseResult actual2 = evaluator.getAffects("7", "7", EntityType::INT, EntityType::INT, true);
			REQUIRE_FALSE(actual2.containsValidResult());

			QueryClauseResult actual3 = evaluator.getAffects("9", "9", EntityType::INT, EntityType::INT, true);
			REQUIRE(actual3.containsValidResult());
		} SECTION ("LHS INT - RHS WILD") {
			QueryClauseResult actual1 = evaluator.getAffects("14", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual1.containsValidResult());

			QueryClauseResult actual2 = evaluator.getAffects("5", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual2.containsValidResult());

			QueryClauseResult actual3 = evaluator.getAffects("15", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual3.containsValidResult());

		} SECTION ("LHS INT - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("19", "s1", EntityType::INT, EntityType::STMT, true);
			REQUIRE_FALSE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("5", "s2", EntityType::INT, EntityType::STMT, false);
			REQUIRE(actualNormRes.containsValidResult());

		} SECTION ("LHS INT - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("18", "a1", EntityType::INT, EntityType::ASSIGN,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("7", "a2", EntityType::INT, EntityType::ASSIGN,
																   false);
			REQUIRE(actualNormRes.getTable().empty());

		} SECTION ("LHS WILD - RHS INT") {
			QueryClauseResult actual = evaluator.getAffects("_", "12", EntityType::WILD, EntityType::INT, true);
			REQUIRE(actual.containsValidResult());

		} SECTION ("LHS WILD - RHS WILD") {
			QueryClauseResult actual = evaluator.getAffects("_", "_", EntityType::WILD, EntityType::WILD, true);
			REQUIRE(actual.containsValidResult());

		} SECTION ("LHS WILD - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("_", "s1", EntityType::WILD, EntityType::STMT, true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("_", "s2", EntityType::WILD, EntityType::STMT,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"s2", {"7", "9", "12", "14", "15", "17", "18", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS WILD - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("_", "a1", EntityType::WILD, EntityType::ASSIGN,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("_", "a2", EntityType::WILD, EntityType::ASSIGN,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"a2", {"7", "9", "12", "14", "15", "17", "18", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS INT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("s1", "17", EntityType::STMT, EntityType::INT, true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("s2", "18", EntityType::STMT, EntityType::INT,
																   false);
			Table expectedNormTable = {{"s2", {"17"}}};
			QueryClauseResult expectedNormRes = QueryClauseResult(expectedNormTable);
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS WILD") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("s1", "_", EntityType::STMT, EntityType::WILD, true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("s2", "_", EntityType::STMT, EntityType::WILD,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"s2", {"4", "5", "9", "11", "12", "14", "15", "16", "17", "18", "20"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("s1", "s2", EntityType::STMT, EntityType::STMT,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("s3", "s4", EntityType::STMT, EntityType::STMT,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult({
																	  {"s3", {"4", "4",  "4",  "4",  "5", "5",  "9", "9",  "9",  "11", "12", "12", "12", "12", "14", "14", "14", "15", "16", "17", "17", "18", "20"}},
																	  {"s4", {"7", "14", "17", "19", "9", "17", "9", "12", "17", "7",  "14", "17", "19", "7",  "15", "17", "19", "17", "17", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("s1", "a1", EntityType::STMT, EntityType::ASSIGN,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("s2", "a2", EntityType::STMT, EntityType::ASSIGN,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult({
																	  {"s2", {"4", "4",  "4",  "4",  "5", "5",  "9", "9",  "9",  "11", "12", "12", "12", "12", "14", "14", "14", "15", "16", "17", "17", "18", "20"}},
																	  {"a2", {"7", "14", "17", "19", "9", "17", "9", "12", "17", "7",  "14", "17", "19", "7",  "15", "17", "19", "17", "17", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS INT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("a1", "11", EntityType::ASSIGN, EntityType::INT,
																   true);
			REQUIRE_FALSE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("a2", "12", EntityType::ASSIGN, EntityType::INT,
																   false);
			Table expectedNormTable = {{"a2", {"9"}}};
			QueryClauseResult expectedNormRes = QueryClauseResult(expectedNormTable);

		} SECTION ("LHS ASSIGN - RHS WILD") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("a1", "_", EntityType::ASSIGN, EntityType::WILD,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("a2", "_", EntityType::ASSIGN, EntityType::WILD,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"a2", {"4", "5", "9", "11", "12", "14", "15", "16", "17",
						 "18", "20"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("a1", "s1", EntityType::ASSIGN, EntityType::STMT,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("a2", "s2", EntityType::ASSIGN, EntityType::STMT,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult({
																	  {"a2", {"4", "4",  "4",  "4",  "5", "5",  "9", "9",  "9",  "11", "12", "12", "12", "12", "14", "14", "14", "15", "16", "17", "17", "18", "20"}},
																	  {"s2", {"7", "14", "17", "19", "9", "17", "9", "12", "17", "7",  "14", "17", "19", "7",  "15", "17", "19", "17", "17", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffects("a1", "a2", EntityType::ASSIGN, EntityType::ASSIGN,
																   true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffects("a3", "a4", EntityType::ASSIGN, EntityType::ASSIGN,
																   false);
			QueryClauseResult expectedNormRes = QueryClauseResult({
																	  {"a3", {"4", "4",  "4",  "4",  "5", "5",  "9", "9",  "9",  "11", "12", "12", "12", "12", "14", "14", "14", "15", "16", "17", "17", "18", "20"}},
																	  {"a4", {"7", "14", "17", "19", "9", "17", "9", "12", "17", "7",  "14", "17", "19", "7",  "15", "17", "19", "17", "17", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		}
	}

	SECTION ("Test affects - negative cases") {
		AffectsEvaluator evaluator;
		SECTION ("LHS READ - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("re", "s", EntityType::READ, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS PRINT - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("pn", "s", EntityType::PRINT, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS CALL - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("c", "s", EntityType::CALL, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS WHILE - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("w", "s", EntityType::WHILE, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS IF - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("ifs", "s", EntityType::IF, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS VAR - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("v", "s", EntityType::VAR, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS CONST - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("co", "s", EntityType::CONST, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS PROC - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffects("p", "s", EntityType::PROC, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS READ") {
			QueryClauseResult actual = evaluator.getAffects("a", "re", EntityType::ASSIGN, EntityType::READ, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS PRINT") {
			QueryClauseResult actual = evaluator.getAffects("a", "pn", EntityType::ASSIGN, EntityType::PRINT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS CALL") {
			QueryClauseResult actual = evaluator.getAffects("a", "c", EntityType::ASSIGN, EntityType::CALL, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS WHILE") {
			QueryClauseResult actual = evaluator.getAffects("a", "w", EntityType::ASSIGN, EntityType::WHILE, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS IF") {
			QueryClauseResult actual = evaluator.getAffects("a", "ifs", EntityType::ASSIGN, EntityType::IF, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS VAR") {
			QueryClauseResult actual = evaluator.getAffects("a", "v", EntityType::ASSIGN, EntityType::VAR, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS CONST") {
			QueryClauseResult actual = evaluator.getAffects("a", "co", EntityType::ASSIGN, EntityType::CONST, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS PROC") {
			QueryClauseResult actual = evaluator.getAffects("a", "p", EntityType::ASSIGN, EntityType::PROC, false);
			REQUIRE_FALSE(actual.containsValidResult());
		}
	}

	SECTION ("Test affects* - positive cases") {
		AffectsEvaluator evaluator;
		SECTION ("LHS INT - RHS INT") {
			QueryClauseResult actual1 = evaluator.getAffectsT("4", "14", EntityType::INT, EntityType::INT, true);
			REQUIRE(actual1.containsValidResult());

			QueryClauseResult actual2 = evaluator.getAffectsT("20", "22", EntityType::INT, EntityType::INT, true);
			REQUIRE_FALSE(actual2.containsValidResult());

			QueryClauseResult actual3 = evaluator.getAffectsT("9", "9", EntityType::INT, EntityType::INT, true);
			REQUIRE(actual3.containsValidResult());

		} SECTION ("LHS INT - RHS WILD") {
			QueryClauseResult actual1 = evaluator.getAffectsT("14", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual1.containsValidResult());

			QueryClauseResult actual2 = evaluator.getAffectsT("4", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual2.containsValidResult());

			QueryClauseResult actual3 = evaluator.getAffectsT("5", "_", EntityType::INT, EntityType::WILD, true);
			REQUIRE(actual3.containsValidResult());

		} SECTION ("LHS INT - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("11", "s1", EntityType::INT, EntityType::STMT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("12", "s2", EntityType::INT, EntityType::STMT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"s2", {"7", "14", "15", "17", "18", "19"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS INT - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("14", "a1", EntityType::INT, EntityType::ASSIGN,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("16", "a2", EntityType::INT, EntityType::ASSIGN,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"a2", {"17", "18", "19"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS WILD - RHS INT") {
			QueryClauseResult actual = evaluator.getAffectsT("_", "19", EntityType::WILD, EntityType::INT, true);
			REQUIRE(actual.containsValidResult());

		} SECTION ("LHS WILD - RHS WILD") {
			QueryClauseResult actual = evaluator.getAffectsT("_", "_", EntityType::WILD, EntityType::WILD, true);
			REQUIRE(actual.containsValidResult());

		} SECTION ("LHS WILD - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("_", "s1", EntityType::WILD, EntityType::STMT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("_", "s2", EntityType::WILD, EntityType::STMT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"s2", {"7", "9", "12", "14", "15", "17", "18", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS WILD - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("_", "a1", EntityType::WILD, EntityType::ASSIGN,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("_", "a2", EntityType::WILD, EntityType::ASSIGN,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"a2", {"7", "9", "12", "14", "15", "17", "18", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS INT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("s1", "17", EntityType::STMT, EntityType::INT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("s2", "18", EntityType::STMT, EntityType::INT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"s2", {"4", "5", "9", "12", "14", "15", "16", "17"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS WILD") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("s1", "_", EntityType::STMT, EntityType::WILD,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("s2", "_", EntityType::STMT, EntityType::WILD,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"s2", {"4", "5", "9", "11", "12", "14", "15", "16", "17", "18", "20"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("s1", "s2", EntityType::STMT, EntityType::STMT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("s3", "s4", EntityType::STMT, EntityType::STMT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"s3",
																	   {"4", "4",  "4",  "4",  "4",  "4",  "5", "5", "5", "5",
																																"5",  "5",  "5",  "5",  "9", "9", "9",  "9", "9",  "9",
																																														 "9",  "9",  "11", "12", "12", "12", "12", "12", "12",
																																																											   "14", "14", "14", "14", "15", "15", "15", "16",
																																																																							   "16", "16", "17", "17", "18", "20"}},
																   {"s4",
																	   {"7", "14", "15", "17", "18", "19", "7", "9", "12",
																														  "14", "15", "17", "18", "19", "7", "9", "12", "14",
																																											 "15", "17", "18", "19", "7",  "7",  "14", "15", "17",
																																																								   "18", "19", "15", "17", "18", "19", "17", "18",
																																																																				   "19", "17", "18", "19", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS STMT - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("s1", "a1", EntityType::STMT, EntityType::ASSIGN,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("s2", "a2", EntityType::STMT, EntityType::ASSIGN,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"s2",
																	   {"4", "4",  "4",  "4",  "4",  "4",  "5", "5", "5", "5",  "5",  "5",  "5",  "5",  "9", "9", "9",  "9", "9",  "9",  "9",  "9",  "11", "12", "12", "12", "12", "12", "12", "14", "14", "14", "14", "15", "15", "15", "16", "16", "16", "17", "17", "18", "20"}},
																   {"a2",
																	   {"7", "14", "15", "17", "18", "19", "7", "9", "12",
																														  "14", "15", "17", "18", "19", "7", "9", "12", "14",
																																											 "15", "17", "18", "19", "7",  "7",  "14", "15", "17", "18", "19", "15", "17", "18", "19", "17", "18", "19", "17", "18", "19", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS INT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("a1", "14", EntityType::ASSIGN, EntityType::INT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("a2", "22", EntityType::ASSIGN, EntityType::INT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"a2", {"4", "5", "9", "12", "14", "15", "16", "17", "18"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS WILD") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("a1", "_", EntityType::ASSIGN, EntityType::WILD,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("a2", "_", EntityType::ASSIGN, EntityType::WILD,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult(
				{{"a2", {"4", "5", "9", "11", "12", "14", "15", "16", "17", "18", "20"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS STMT") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("a1", "s1", EntityType::ASSIGN, EntityType::STMT,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("a2", "s2", EntityType::ASSIGN, EntityType::STMT,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"a2",
																	   {"4", "4",  "4",  "4",  "4",  "4",  "5", "5", "5", "5",
																																"5",  "5",  "5",  "5",  "9", "9", "9",  "9", "9",  "9",
																																														 "9",  "9",  "11", "12", "12", "12", "12", "12", "12",
																																																											   "14", "14", "14", "14", "15", "15", "15", "16",
																																																																							   "16", "16", "17", "17", "18", "20"}},
																   {"s2",
																	   {"7", "14", "15", "17", "18", "19", "7", "9", "12",
																														  "14", "15", "17", "18", "19", "7", "9", "12", "14",
																																											 "15", "17", "18", "19", "7",  "7",  "14", "15", "17",
																																																								   "18", "19", "15", "17", "18", "19", "17", "18",
																																																																				   "19", "17", "18", "19", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		} SECTION ("LHS ASSIGN - RHS ASSIGN") {
			QueryClauseResult actualBoolRes = evaluator.getAffectsT("a1", "a2", EntityType::ASSIGN, EntityType::ASSIGN,
																	true);
			REQUIRE(actualBoolRes.containsValidResult());

			QueryClauseResult actualNormRes = evaluator.getAffectsT("a3", "a4", EntityType::ASSIGN, EntityType::ASSIGN,
																	false);
			QueryClauseResult expectedNormRes = QueryClauseResult({{"a3",
																	   {"4", "4",  "4",  "4",  "4",  "4",  "5", "5", "5", "5",
																																"5",  "5",  "5",  "5",  "9", "9", "9",  "9", "9",  "9",
																																														 "9",  "9",  "11", "12", "12", "12", "12", "12", "12",
																																																											   "14", "14", "14", "14", "15", "15", "15", "16",
																																																																							   "16", "16", "17", "17", "18", "20"}},
																   {"a4",
																	   {"7", "14", "15", "17", "18", "19", "7", "9", "12",
																														  "14", "15", "17", "18", "19", "7", "9", "12", "14",
																																											 "15", "17", "18", "19", "7",  "7",  "14", "15", "17",
																																																								   "18", "19", "15", "17", "18", "19", "17", "18",
																																																																				   "19", "17", "18", "19", "18", "19", "19", "21"}}});
			REQUIRE(actualNormRes == expectedNormRes);

		}
	}

	SECTION ("Test affects* - negative cases") {
		AffectsEvaluator evaluator;
		SECTION ("LHS READ - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("re", "s", EntityType::READ, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS PRINT - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("pn", "s", EntityType::PRINT, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS CALL - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("c", "s", EntityType::CALL, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS WHILE - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("w", "s", EntityType::WHILE, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS IF - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("ifs", "s", EntityType::IF, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS VAR - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("v", "s", EntityType::VAR, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS CONST - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("co", "s", EntityType::CONST, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS PROC - RHS STMT") {
			QueryClauseResult actual = evaluator.getAffectsT("p", "s", EntityType::PROC, EntityType::STMT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS READ") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "re", EntityType::ASSIGN, EntityType::READ, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS PRINT") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "pn", EntityType::ASSIGN, EntityType::PRINT, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS CALL") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "c", EntityType::ASSIGN, EntityType::CALL, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS WHILE") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "w", EntityType::ASSIGN, EntityType::WHILE, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS IF") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "ifs", EntityType::ASSIGN, EntityType::IF, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS VAR") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "v", EntityType::ASSIGN, EntityType::VAR, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS CONST") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "co", EntityType::ASSIGN, EntityType::CONST, false);
			REQUIRE_FALSE(actual.containsValidResult());
		} SECTION ("LHS ASSIGN - RHS PROC") {
			QueryClauseResult actual = evaluator.getAffectsT("a", "p", EntityType::ASSIGN, EntityType::PROC, false);
			REQUIRE_FALSE(actual.containsValidResult());
		}
	}
	PKB::clearAllStores();
}
