#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("multiple pattern clause with AND") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("test case 1") {
		std::string queryString = "assign a,a1; variable v; Select a pattern a(v,_) and a1(v,_\"pi * diameter * 1234\"_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));

		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("a");
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms, "a"));

		clauseArgs.clear();
		usedSynonyms.clear();

		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("_pi diameter * 1234 *_"), EntityType::STRING));
		usedSynonyms.insert("a1");
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_ASSIGN, clauseArgs, usedSynonyms,"a1"));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}