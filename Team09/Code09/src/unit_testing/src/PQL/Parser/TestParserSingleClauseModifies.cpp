#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

//---------------------------------------------------------------//
//			                Happy Paths			                 //
//---------------------------------------------------------------//

//---------------------------------//
//     2nd arg is var synonym	   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 1 : M(s,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "stmt s; variable v; Select v such that Modifies(s,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("s");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}


TEST_CASE("PQL parser single clause test case 2 : M(a,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; variable v; Select v such that Modifies(a,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("a");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 3 : M(re,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "read re; variable v; Select v such that Modifies(re,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("re");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 4: M(pn,v) print not allowed for modified statements") {
	std::string queryString = "print pn; variable v; Select v such that Modifies(pn,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("PQL parser single clause test case 5: M(w,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while w; variable v; Select v such that Modifies(w,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("w");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 6: M(ifs,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "if ifs; variable v; Select v such that Modifies(ifs,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("ifs");
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 7: M(2,v)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "variable v; Select v such that Modifies(2,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	usedSynonyms.insert("v");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}


//---------------------------------//
//     2nd arg is var name		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 8 : M(s,\"vs\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "stmt s; variable v; Select s such that Modifies(s,\"vs\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
	clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
	clauseArgs.push_back(QueryArgument(std::string("vs"), EntityType::STRING));
	usedSynonyms.insert("s");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 9 : M(a,\"v\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; variable v; Select a such that Modifies(a,\"v\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
	usedSynonyms.insert("a");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 10 : M(re,\"variable\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "read re; variable v; Select re such that Modifies(re,\"variable\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
	clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
	clauseArgs.push_back(QueryArgument(std::string("variable"), EntityType::STRING));
	usedSynonyms.insert("re");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}


TEST_CASE("PQL parser single clause test case 12: M(w,\"vN\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while w; variable v; Select w such that Modifies(w,\"vN\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("vN"), EntityType::STRING));
	usedSynonyms.insert("w");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 13: M(ifs,\"v1\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "if ifs; variable v; Select ifs such that Modifies(ifs,\"v1\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
	clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
	clauseArgs.push_back(QueryArgument(std::string("v1"), EntityType::STRING));
	usedSynonyms.insert("ifs");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 14: M(2,\"v2\")") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "variable v; Select v such that Modifies(2,\"v2\")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
	clauseArgs.push_back(QueryArgument(std::string("v2"), EntityType::STRING));
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

//---------------------------------//
//     2nd arg is wildcard		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 15 : M(s,_) + tab line in between args") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "stmt s; variable v; Select s such that Modifies(s,\t_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
	clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	usedSynonyms.insert("s");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 16 : M(a,_) + new line in between args") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "assign a; variable v; Select a such that Modifies(a, \n _)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));

	usedSynonyms.insert("a");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 17 : M(re,_) + multiple whitespaces") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "read re; variable v; Select re such that Modifies(re,         _)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
	clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	usedSynonyms.insert("re");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 19: M(w,_) + multiple new line") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "while w; variable v; Select w such that Modifies(w,\n\n\n_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	usedSynonyms.insert("w");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 20: M(ifs,_)") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "if ifs; variable v; Select ifs such that Modifies(ifs,_)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
	clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	usedSynonyms.insert("ifs");
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

TEST_CASE("PQL parser single clause test case 21: M(2,_) + whitespace") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;
	std::string queryString = "variable v; Select v such that Modifies(2, _)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
	clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
	clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
	expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, usedSynonyms));

	Query actualQuery = parser.parse();
	std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
	std::vector<QueryClause> actualClauses = actualQuery.getClauses();
	bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
	bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
	REQUIRE((isClausesEqual && isResultSynonymEqual));
}

//---------------------------------------------------------------//
//			               unhappy Paths			             //
//---------------------------------------------------------------//

//---------------------------------//
//     1st arg is var wildcard	 //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 22: M(_,v)") {
	std::string queryString = "variable v; Select v such that Modifies(_,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
  REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//     1st arg is type const		 //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 23: M(c,v)") {
	std::string queryString = "variable v; constant c; Select v such that Modifies(c,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
  REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//     1st arg is type variable	 //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 24: M(v2,v)") {
	std::string queryString = "variable v,v2; Select v such that Modifies(v2,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//		missing close paran		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 25: missing close paran	") {
	std::string queryString = "variable v,v2; Select v such that Modifies(v2,v";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//		missing close paran		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 26: missing close paran	") {
	std::string queryString = "variable v,v2; Select v such that Modifies v2,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//		missing comma		       //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 27: missing comma") {
	std::string queryString = "variable v,v2; Select v such that Modifies (v2 v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//		missing first arg		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 28: missing first arg	") {
	std::string queryString = "variable v,v2; Select v such that Modifies ( ,v)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//		missing second arg		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 29: missing second arg") {
	std::string queryString = "variable v,v2; Select v such that Modifies ( v,)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//			missing  Modifies		//
//---------------------------------//

TEST_CASE("PQL parser single clause test case 30: missing  Modifies") {
	std::string queryString = "variable v,v2; Select v such that  ( v,)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//			missing such		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 31: missing such	") {
	std::string queryString = "variable v,v2; Select v that Modifies ( v,)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

//---------------------------------//
//			missing that		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 32: missing that	") {
	std::string queryString = "variable v,v2; Select v such Modifies ( v,)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}


//---------------------------------//
//		  missing such that		   //
//---------------------------------//

TEST_CASE("PQL parser single clause test case 33: missing such that") {
	std::string queryString = "variable v,v2; Select v such Modifies ( v,)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}
