#include "catch.hpp"
#include "PQL/Parser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL parser such that clause test case 1") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses; 
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while w;\nSelect w such that Parent*(1,w)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();
	Parser PQLParser = Parser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
	clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	usedSynonyms.insert("w");
	expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

	Query actualQuery = PQLParser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}
