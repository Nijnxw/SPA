#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL parser single clause test case 1 : Pa(s,_)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; variable v; Select a pattern a(v,_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	usedSynonyms.insert("a");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::PATTERN, clauseArgs, usedSynonyms, "a"));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}


TEST_CASE("PQL parser single clause test case 2 : Pa(s,_\"a\"_") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; variable v; Select a pattern a(v,_\"a\"_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("_a_"), EntityType::STRING));
	usedSynonyms.insert("a");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::PATTERN, clauseArgs, usedSynonyms, "a"));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("pql parser single clause test case 3: pa(\"s\", _)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; Select a pattern a(\"v\", _\"a\"_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
	clauseArgs.push_back(QueryArgument(std::string("_a_"), EntityType::STRING));
	usedSynonyms.insert("a");
	expectedClauses.push_back(QueryClause(RelationRef::PATTERN, clauseArgs, usedSynonyms, "a"));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}