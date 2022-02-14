#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL parser Select only test case 1 : valid synonym after select") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "stmt s; Select s ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 2 : valid synonym after select 2") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "variable v123; Select v123 ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v123"), EntityType::VAR));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 3: multi declaration select 3") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "constant c1,c2; Select c2 ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("c2"), EntityType::CONST));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 4 : keyword after select") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "print Pattern; Select Pattern ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("Pattern"), EntityType::PRINT));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 5 : keyword after select 2") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign assign; Select assign ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("assign"), EntityType::ASSIGN));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 6 : keyword after select 3") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "if Parent; Select Parent ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("Parent"), EntityType::IF));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 7 : keyword after select 4") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "read Follows; Select Follows ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("Follows"), EntityType::READ));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 8 : keyword after select 5") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "procedure Uses; Select Uses ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("Uses"), EntityType::PROC));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 9 : keyword after select 6") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while Modifies; Select Modifies ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("Modifies"), EntityType::WHILE));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

//---------------------------------//
//  graceful handling of failure   //
//---------------------------------//

TEST_CASE("PQL parser Select only test case 10 : invalid synonym as result synonym") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while 1w; Select 1w ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 11 : integer as result synonym") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "variable 1; Select 1 ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 12 : result synonym does not exist") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "constant c; Select c1 ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 13 : no declarations") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "read ; Select r1 ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser Select only test case 14 : no result synonym") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; Select  ";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}


