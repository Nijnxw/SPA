#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

//---------------------------------------------------------------//
//			                Happy Paths			                 //
//---------------------------------------------------------------//

//---------------------------------//
//     2nd arg is assign synonym   //
//---------------------------------//

TEST_CASE("Affects - 2nd arg is assign synonym") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("A(3,a)") {
		std::string queryString = "assign a; Select a such that Affects(3,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(s,a)") {
		std::string queryString = "stmt s; assign a; Select a such that Affects(s,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("s");
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(_,a)") {

		std::string queryString = "assign a; Select a such that Affects(_,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(a1, a)") {
		std::string queryString = " assign a, a1; Select a1 such that Affects(a1,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a1");
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

//---------------------------------//
//     2nd arg is integer		   //
//---------------------------------//

TEST_CASE("Affects - 2nd arg is integer") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("A(3,4)") {
		std::string queryString = "assign a; Select a such that Affects(3,4)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(s,5)") {
		std::string queryString = "stmt s; assign a; Select s such that Affects(s,5)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("5"), EntityType::INT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(_,7)") {

		std::string queryString = "assign a; Select a such that Affects(_,7)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("7"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(a1, 8)") {
		std::string queryString = " assign a, a1; Select a1 such that Affects(a1,8)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("8"), EntityType::INT));
		usedSynonyms.insert("a1");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

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

TEST_CASE("Affects - 2nd arg is wildcard") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("A(3,_)") {
		std::string queryString = "assign a; Select a such that Affects(3,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(s,_)") {
		std::string queryString = "stmt s; assign a; Select s such that Affects(s,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(_,_)") {

		std::string queryString = "assign a; Select a such that Affects(_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(a1, _)") {
		std::string queryString = " assign a, a1; Select a1 such that Affects(a1,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("a1");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

//---------------------------------//
//     2nd arg is stmt syn		   //
//---------------------------------//

TEST_CASE("Affects - 2nd arg is stmt syn") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("A(3,s)") {
		std::string queryString = "stmt s; Select s such that Affects(3,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(s,s1)") {
		std::string queryString = "stmt s,s1; Select s1 such that Affects(s,s1)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s1"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s1"), EntityType::STMT));
		usedSynonyms.insert("s");
		usedSynonyms.insert("s1");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(_,s)") {

		std::string queryString = "stmt s; Select s such that Affects(_,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("A(a1, s)") {
		std::string queryString = " assign a1; stmt s; Select a1 such that Affects(a1,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("a1");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::AFFECTS, clauseArgs, usedSynonyms));

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

TEST_CASE("Affects - print synonym as first arg") {
	std::string queryString = "print pn; assign a; Select a such that Affects(pn,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Affects - var synonym as first arg") {
	std::string queryString = "variable v; assign a; Select a such that Affects(v,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Affects - const synonym as first arg") {
	std::string queryString = "assign a; constant c; Select a such that Affects(c,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - if synonym as first arg") {
	std::string queryString = "if ifs; assign a; Select a such that Affects(ifs,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Affects - while synonym as first arg") {
	std::string queryString = "while w; assign a; Select a such that Affects(w,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE(actualQuery.isEmpty());
}

TEST_CASE("Affects - read synonym as first arg") {
	std::string queryString = "assign a; read rd; Select a such that Affects(rd,a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - missing open paran") {
	std::string queryString = "assign a; select a such that Affects a, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - missing first") {
	std::string queryString = "assign a; select a such that Affects (, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - missing comma") {
	std::string queryString = "assign a; select a such that Affects (a 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - missing second arg") {
	std::string queryString = "assign a; select a such that Affects (a, )";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - missing close paran") {
	std::string queryString = "assign a; select a such that Affects (a, 1";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Affects - insufficient arguments") {
	std::string queryString = "assign a; select a such that Affects (a)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}