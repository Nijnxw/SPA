#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("pattern - if pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("variable as first arg") {

		std::string queryString = "if ifs; variable v; Select ifs pattern ifs(v,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("ifs");
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_IF, clauseArgs, usedSynonyms, "ifs"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("wild as first arg") {
		std::string queryString = "if ifs; Select ifs pattern ifs(_,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_IF, clauseArgs, usedSynonyms, "ifs"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("string as first arg") {
		std::string queryString = "if ifs; Select ifs pattern ifs(\"v\",_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_IF, clauseArgs, usedSynonyms, "ifs"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("pattern - if pattern unhappy paths") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("expected stmt list") {
		std::string queryString = "if ifs; variable v; stmt s; Select ifs pattern ifs(v,s,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("non var arg synonym as first arg") {
		std::string queryString = "if ifs; variable v; stmt s; Select ifs pattern ifs(s,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("integer as first arg") {
		std::string queryString = "if ifs; variable v; stmt s; Select ifs pattern ifs(1,_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("expr as first arg") {
		std::string queryString = "if ifs; variable v; stmt s; Select ifs pattern ifs(\"123\",_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}