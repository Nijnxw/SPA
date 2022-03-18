#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("pattern - while pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("variable as first arg") {
		std::string queryString = "while w; variable v; Select w pattern w(v,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("w");
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_WHILE, clauseArgs, usedSynonyms, "w"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("wild as first arg") {
		std::string queryString = "while w; Select w pattern w(_,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_WHILE, clauseArgs, usedSynonyms, "w"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("string as first arg") {
		std::string queryString = "while w; Select w pattern w(\"v\",_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_WHILE, clauseArgs, usedSynonyms, "w"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("pattern - while pattern unhappy paths") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("expected stmt list") {
		std::string queryString = "while w; variable v; stmt s; Select w pattern w(v,s,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("non var arg synonym as first arg") {
		std::string queryString = "while w; variable v; stmt s; Select w pattern w(s,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("integer as first arg") {
		std::string queryString = "while w; variable v; stmt s; Select w pattern w(1,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("expr as first arg") {
		std::string queryString = "while w; variable v; stmt s; Select w pattern w(\"123\",_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}