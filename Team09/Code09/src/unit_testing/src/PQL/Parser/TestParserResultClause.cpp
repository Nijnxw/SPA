#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("Tuple result clause") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("test case 1") {
		std::string queryString = "assign a,a1; variable v; Select <a,a1,v> ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("BOOLEAN result clause") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("test case 1") {
		std::string queryString = "assign a,a1; variable v; Select BOOLEAN ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		bool isBooleanQuery = actualQuery.isBooleanQuery();
		REQUIRE(isBooleanQuery);
	}
}