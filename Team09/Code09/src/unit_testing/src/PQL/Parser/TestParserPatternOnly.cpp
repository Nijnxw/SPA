#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("pattern - variable synonym as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("wildcard as second arg") {
		std::string queryString = "assign a; variable v; Select a pattern a(v,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("a");
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("variable factor as second arg") {
		std::string queryString = "assign a2; variable v1; Select a2 pattern a2(v1,_\"x\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a2"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v1"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_x_"), EntityType::STRING));
		usedSynonyms.insert("a2");
		usedSynonyms.insert("v1");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a2"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("integer factor as second arg") {
		std::string queryString = "assign a1; variable v2; Select a1 pattern a1(v2,_\"1\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v2"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_1_"), EntityType::STRING));
		usedSynonyms.insert("a1");
		usedSynonyms.insert("v2");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a1"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("expr as second arg") {
		std::string queryString = "assign a1; variable v2; Select a1 pattern a1(v2,_\"1 + 2 + x + x1 * x2 - x3\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v2"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_1 2 + x + x1 x2 * + x3 -_"), EntityType::STRING));
		usedSynonyms.insert("a1");
		usedSynonyms.insert("v2");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a1"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
			actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("pattern - string (which represents a variable in SIMPLE) as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("wildcard as second arg") {
		std::string queryString = "assign a; Select a pattern a(\"var\",_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("var"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("variable factor as second arg") {
		std::string queryString = "assign a; Select a pattern a(\"y\",_\"z\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("y"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_z_"), EntityType::STRING));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("integer factor as second arg") {
		std::string queryString = "assign a; Select a pattern a(\"z\",_\"123\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("z"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_123_"), EntityType::STRING));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("pattern - wildcard as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("wildcard as second arg") {
		std::string queryString = "assign a; Select a pattern a(_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("variable factor as second arg") {
		std::string queryString = "assign a; Select a pattern a(_,_\"abc\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_abc_"), EntityType::STRING));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("integer factor as second arg") {
		std::string queryString = "assign a; Select a pattern a(_,_\"456\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_456_"), EntityType::STRING));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("pattern - different assign-syn") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	std::string queryString = "assign a,a1; variable v;Select a pattern a1(v, _\"879\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("_879_"), EntityType::STRING));
	usedSynonyms.insert("a1");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a1"));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
										   actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("pattern - expr pattern 1") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	std::string queryString = "assign a1; variable v;Select a1 pattern a1(v, _\"((((((879))))))\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("_879_"), EntityType::STRING));
	usedSynonyms.insert("a1");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a1"));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
		actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("invalid expr 1") {
	std::string queryString = "assign a; variable v; Select a pattern a(v, _\"xH 123 + 456\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("invalid expr 2") {
	std::string queryString = "assign a; variable v; Select a pattern a(v, _\"xH - ( 123 + 456\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("invalid expr 3") {
	std::string queryString = "assign a; variable v; Select a pattern a(v, _\"xH + () + 123 + 456\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("invalid expr 4") {
	std::string queryString = "assign a; variable v; Select a pattern a(v, _\"xH  123 + 456)\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("non-var syn as first argument") {
	std::string queryString = "assign a; read re; Select a pattern a(re, _\"xH\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("illegal factor first argument") {
	std::string queryString = "assign a; Select a pattern a(_, _\"1xH3\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("integer as first argument") {
	std::string queryString = "assign a; Select a pattern a(1, _\"xH\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("invalid factor, missing right underscore") {
	std::string queryString = "assign a; variable v; Select a pattern a(v, _\"f2\")";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("invalid factor, missing left underscore") {
	std::string queryString = "assign a; Select a pattern a(\"v123\", \"f2\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing assign-syn") {
	std::string queryString = "assign a; Select a pattern (_,_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing open paranthesis") {
	std::string queryString = "assign a; variable v456; Select a pattern a v456,_\"y12\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing first arg") {
	std::string queryString = "assign a; variable v789; Select a pattern a(,_\"123\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing comma ") {
	std::string queryString = "assign a; variable va78; Select a pattern a(va78 _\"y123\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing second arg ") {
	std::string queryString = "assign a; Select a pattern a(_, )";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("missing close paranthesis") {
	std::string queryString = "assign a; Select a pattern a(\"v123\", _\"z3\"_ ";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("only 1 arg") {
	std::string queryString = "assign a; variable v; Select a pattern a(v)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}
