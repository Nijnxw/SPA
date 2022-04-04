#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("multiple declared synonyms") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("Duplicated declarations in same entity declaration ") {
		std::string queryString = "stmt s,s; Select s ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}

	SECTION("Duplicated declarations in same entity declaration ") {
		std::string queryString = "stmt s; variable s; Select s ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}
}