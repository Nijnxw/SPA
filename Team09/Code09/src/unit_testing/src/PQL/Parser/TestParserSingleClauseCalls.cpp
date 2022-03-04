#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

//---------------------------------------------------------------//
//			                Happy Paths			                 //
//---------------------------------------------------------------//

//---------------------------------//
//     2nd arg is var synonym	   //
//---------------------------------//

TEST_CASE("Calls - 2nd arg is proc synonym") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("C(p,p1)") {
		std::string queryString = "procedure p,p1; Select p such that Calls(p,p1)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("p1"), EntityType::PROC));
		usedSynonyms.insert("p");
		usedSynonyms.insert("p1");
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(\"main\",v)") {
		std::string queryString = "procedure p; Select p such that Calls(\"main\",p)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("main"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		usedSynonyms.insert("p");
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(_,p)") {

		std::string queryString = "procedure p; Select p such that Calls(_,p)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		usedSynonyms.insert("p");
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}
//---------------------------------//
//     2nd arg is proc name		   //
//---------------------------------//

TEST_CASE("Calls - 2nd arg is var name") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("C(p,\"test1\")") {
		std::string queryString = "procedure p; Select p such that Calls(p,\"test1\")";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("test1"), EntityType::STRING));
		usedSynonyms.insert("p");
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(\"main\",\"test2\")") {
		std::string queryString = "procedure p; Select p such that Calls(\"main\",\"test2\")";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("main"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("test2"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(_,\"test3\")") {

		std::string queryString = "procedure p; Select p such that Calls(_,\"test3\")";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("test3"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}
//---------------------------------//
//     2nd arg is wildcard		   //
//---------------------------------//

TEST_CASE("Calls - 2nd arg is wildcard") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("C(p,_)") {
		std::string queryString = "procedure p; Select p such that Calls(p,_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("p");
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(\"main\",_)") {
		std::string queryString = "procedure p; Select p such that Calls(\"main\",_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("main"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("c(_,_)") {

		std::string queryString = "procedure p; Select p such that Calls(_,_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::CALLS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

//---------------------------------------------------------------//
//			               unhappy Paths			             //
//---------------------------------------------------------------//

TEST_CASE("Calls - read synonym as first arg") {
	std::string queryString = "read re; procedure p; Select p such that Calls(re,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Calls - var synonym as first arg") {
	std::string queryString = "variable v; procedure p; Select p such that Calls(v,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Calls - const synonym as first arg") {
	std::string queryString = "procedure p; constant c; Select p such that Calls(c,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - print synonym as first arg") {
	std::string queryString = "print pn; procedure p; Select p such that Calls(pn,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Calls - stmt synonym as first arg") {
	std::string queryString = "stmt s; procedure p; Select p such that Calls(s,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Calls - if synonym as first arg") {
	std::string queryString = "procedure p; if ifs; Select p such that Calls(ifs,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - while synonym as first arg") {
	std::string queryString = "procedure p; while w; Select p such that Calls(w,p)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - missing open paran") {
	std::string queryString = "assign a; select a such that Calls a, 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - missing first") {
	std::string queryString = "assign a; select a such that Calls (, 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - missing comma") {
	std::string queryString = "assign a; select a such that Calls (a 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - missing second arg") {
	std::string queryString = "assign a; select a such that Calls (a, )";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - missing close paran") {
	std::string queryString = "assign a; select a such that Calls (a, 1";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Calls - insufficient arguments") {
	std::string queryString = "assign a; select a such that Calls (a)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}
