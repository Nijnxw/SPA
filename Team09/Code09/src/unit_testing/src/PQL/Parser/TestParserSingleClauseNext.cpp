#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("Next - integer as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("N(1,re)") {
		std::string queryString = "read re; Select re such that Next(1,re)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(2,s)") {
		std::string queryString = "stmt s; Select s such that Next(2,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(3,w)") {
		std::string queryString = "while w; Select w such that Next(3,w)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(4,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Next(4,ifs)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(5,a)") {
		std::string queryString = "assign a; Select a such that Next(5,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("5"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(6,pn)") {
		std::string queryString = "print pn; Select pn such that Next(6,pn)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("6"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(7,_)") {
		std::string queryString = "stmt s; Select s such that Next(7,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("7"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(8,9)") {
		std::string queryString = "stmt s; Select s such that Next(8,9)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("8"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("9"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Next - wildcard as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("N(_,re)") {
		std::string queryString = "read re; Select re such that Next(_,re)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,s)") {
		std::string queryString = "stmt s; Select s such that Next(_,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,w)") {
		std::string queryString = "while w; Select w such that Next(_,w)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Next(_,ifs)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,a)") {
		std::string queryString = "assign a; Select a such that Next(_,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,pn)") {
		std::string queryString = "print pn; Select pn such that Next(_,pn)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,_)") {
		std::string queryString = "stmt s; Select s such that Next(_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(_,10)") {
		std::string queryString = "stmt s; Select s such that Next(_,10)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("10"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Next - synonym that refers to a statement as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("N(re,s)") {
		std::string queryString = "read re; stmt s; Select re such that Next(re, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("re");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(s2,s)") {
		std::string queryString = "stmt s,s2; Select s such that Next(s2, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s2"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s2");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(w,s)") {
		std::string queryString = "while w; stmt s; Select w such that Next(w, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("w");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(ifs,s)") {
		std::string queryString = "if ifs; stmt s; Select ifs such that Next(ifs, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("ifs");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(a,s)") {
		std::string queryString = "assign a; stmt s; Select a such that Next(a, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("a");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(pn,s)") {
		std::string queryString = "print pn; stmt s; Select pn such that Next(pn, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("pn");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(s, _)") {
		std::string queryString = "stmt s; Select s such that Next(s, _)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("N(s, 123)") {
		std::string queryString = "stmt s; Select s such that Next(s, 123)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("123"), EntityType::INT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::NEXT, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Next - illegal first arg") {

	SECTION("string as first arg") {
		std::string queryString = "stmt s; Select s such that Next(\"asdf\", s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as first arg") {
		std::string queryString = "stmt s; variable v; Select s such that Next(v, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as first arg") {
		std::string queryString = "stmt s; const c; Select s such that Next(c, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as first arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Next(p, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Next - illegal second arg") {

	SECTION("string as second arg") {
		std::string queryString = "stmt s; Select s such that Next(s, \"asdfe\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as second arg") {
		std::string queryString = "stmt s; variable v; Select s such that Next(s, v)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as second arg") {
		std::string queryString = "stmt s; const c; Select s such that Next(s,c)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as second arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Next(s,p)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Next - missing open paran") {
	std::string queryString = "stmt s; select s such that Next s, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Next - missing first") {
	std::string queryString = "stmt s; select s such that Next (, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Next - missing comma") {
	std::string queryString = "stmt s; select s such that Next (s 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Next - missing second arg") {
	std::string queryString = "stmt s; select s such that Next (s, )";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Next - missing close paran") {
	std::string queryString = "stmt s; select s such that Next (s, 1";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Next - insufficient arguments") {
	std::string queryString = "stmt s; Select s such that Next(s)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}