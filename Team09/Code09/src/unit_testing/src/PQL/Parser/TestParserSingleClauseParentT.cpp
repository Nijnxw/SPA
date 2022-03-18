#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("Parent* - integer as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("P*(1,re)") {
		std::string queryString = "read re; Select re such that Parent*(1,re)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(2,s)") {
		std::string queryString = "stmt s; Select s such that Parent*(2,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(3,w)") {
		std::string queryString = "while w; Select w such that Parent*(3,w)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(4,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Parent*(4,ifs)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(5,a)") {
		std::string queryString = "assign a; Select a such that Parent*(5,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("5"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(6,pn)") {
		std::string queryString = "print pn; Select pn such that Parent*(6,pn)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("6"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(7,_)") {
		std::string queryString = "stmt s; Select s such that Parent*(7,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("7"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(8,9)") {
		std::string queryString = "stmt s; Select s such that Parent*(8,9)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("8"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("9"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Parent* - wildcard as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("P*(_,re)") {
		std::string queryString = "read re; Select re such that Parent*(_,re)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,s)") {
		std::string queryString = "stmt s; Select s such that Parent*(_,s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,w)") {
		std::string queryString = "while w; Select w such that Parent*(_,w)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Parent*(_,ifs)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,a)") {
		std::string queryString = "assign a; Select a such that Parent*(_,a)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,pn)") {
		std::string queryString = "print pn; Select pn such that Parent*(_,pn)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,_)") {
		std::string queryString = "stmt s; Select s such that Parent*(_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(_,10)") {
		std::string queryString = "stmt s; Select s such that Parent*(_,10)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("10"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Parent* - synonym that refers to a statement as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("P*(re,s)") {
		std::string queryString = "read re; stmt s; Select re such that Parent*(re, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("re");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(s2,s)") {
		std::string queryString = "stmt s,s2; Select s such that Parent*(s2, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s2"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s2");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(w,s)") {
		std::string queryString = "while w; stmt s; Select w such that Parent*(w, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("w");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(ifs,s)") {
		std::string queryString = "if ifs; stmt s; Select ifs such that Parent*(ifs, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("ifs");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(a,s)") {
		std::string queryString = "assign a; stmt s; Select a such that Parent*(a, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("a");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(pn,s)") {
		std::string queryString = "print pn; stmt s; Select pn such that Parent*(pn, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("pn");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(s, _)") {
		std::string queryString = "stmt s; Select s such that Parent*(s, _)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("P*(s, 123)") {
		std::string queryString = "stmt s; Select s such that Parent*(s, 123)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("123"), EntityType::INT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Parent* - illegal first arg") {

	SECTION("string as first arg") {
		std::string queryString = "stmt s; Select s such that Parent*(\"asdf\", s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as first arg") {
		std::string queryString = "stmt s; variable v; Select s such that Parent*(v, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as first arg") {
		std::string queryString = "stmt s; const c; Select s such that Parent*(c, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as first arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Parent*(p, s)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Parent* - illegal second arg") {

	SECTION("string as second arg") {
		std::string queryString = "stmt s; Select s such that Parent*(s, \"asdfe\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as second arg") {
		std::string queryString = "stmt s; variable v; Select s such that Parent*(s, v)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as second arg") {
		std::string queryString = "stmt s; const c; Select s such that Parent*(s,c)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as second arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Parent*(s,p)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Parent* - missing open paran") {
	std::string queryString = "stmt s; select s such that Parent* s, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Parent* - missing first") {
	std::string queryString = "stmt s; select s such that Parent* (, 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Parent* - missing comma") {
	std::string queryString = "stmt s; select s such that Parent* (s 1)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Parent* - missing second arg") {
	std::string queryString = "stmt s; select s such that Parent* (s, )";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Parent* - missing close paran") {
	std::string queryString = "stmt s; select s such that Parent* (s, 1";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Parent* - insufficient arguments") {
	std::string queryString = "stmt s; Select s such that Parent*(s)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}