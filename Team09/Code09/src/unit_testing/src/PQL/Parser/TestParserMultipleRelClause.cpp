#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("multiple rel clause with AND") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("test case 1") {
		std::string queryString = "read re; Select re such that Next(1,re) and Next(2,3)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		clauseArgs.clear();
		usedSynonyms.clear();

		clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));

		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}