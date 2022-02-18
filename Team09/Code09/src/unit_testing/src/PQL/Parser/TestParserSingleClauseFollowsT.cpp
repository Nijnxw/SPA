#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("Follows* - integer as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("F*(1,re)") {
		std::string queryString = "read re; Select re such that Follows*(1,re)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(2,s)") {
		std::string queryString = "stmt s; Select s such that Follows*(2,s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(3,w)") {
		std::string queryString = "while w; Select w such that Follows*(3,w)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(4,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Follows*(4,ifs)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(5,a)") {
		std::string queryString = "assign a; Select a such that Follows*(5,a)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("5"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(6,pn)") {
		std::string queryString = "print pn; Select pn such that Follows*(6,pn)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("6"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(7,_)") {
		std::string queryString = "stmt s; Select s such that Follows*(7,_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("7"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(8,9)") {
		std::string queryString = "stmt s; Select s such that Follows*(8,9)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("8"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("9"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Follows* - wildcard as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("F*(_,re)") {
		std::string queryString = "read re; Select re such that Follows*(_,re)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		usedSynonyms.insert("re");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,s)") {
		std::string queryString = "stmt s; Select s such that Follows*(_,s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,w)") {
		std::string queryString = "while w; Select w such that Follows*(_,w)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,ifs)") {
		std::string queryString = "if ifs; Select ifs such that Follows*(_,ifs)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,a)") {
		std::string queryString = "assign a; Select a such that Follows*(_,a)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,pn)") {
		std::string queryString = "print pn; Select pn such that Follows*(_,pn)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,_)") {
		std::string queryString = "stmt s; Select s such that Follows*(_,_)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(_,10)") {
		std::string queryString = "stmt s; Select s such that Follows*(_,10)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		clauseArgs.push_back(QueryArgument(std::string("10"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Follows* - synonym that refers to a statement as first arg") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("F*(re,s)") {
		std::string queryString = "read re; stmt s; Select re such that Follows*(re, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("re"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("re");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(s2,s)") {
		std::string queryString = "stmt s,s2; Select s such that Follows*(s2, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s2"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("s2");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(w,s)") {
		std::string queryString = "while w; stmt s; Select w such that Follows*(w, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("w");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(ifs,s)") {
		std::string queryString = "if ifs; stmt s; Select ifs such that Follows*(ifs, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("ifs");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(a,s)") {
		std::string queryString = "assign a; stmt s; Select a such that Follows*(a, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("a");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(pn,s)") {
		std::string queryString = "print pn; stmt s; Select pn such that Follows*(pn, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		usedSynonyms.insert("pn");
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(s, _)") {
		std::string queryString = "stmt s; Select s such that Follows*(s, _)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("F*(s, 123)") {
		std::string queryString = "stmt s; Select s such that Follows*(s, 123)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("123"), EntityType::INT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Follows* - illegal first arg") {

	SECTION("string as first arg") {
		std::string queryString = "stmt s; Select s such that Follows*(\"asdf\", s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as first arg") {
		std::string queryString = "stmt s; variable v; Select s such that Follows*(v, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as first arg") {
		std::string queryString = "stmt s; const c; Select s such that Follows*(c, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as first arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Follows*(p, s)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Follows* - illegal second arg") {

	SECTION("string as second arg") {
		std::string queryString = "stmt s; Select s such that Follows*(s, \"asdfe\")";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("var synonym as second arg") {
		std::string queryString = "stmt s; variable v; Select s such that Follows*(s, v)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("const synonym as second arg") {
		std::string queryString = "stmt s; const c; Select s such that Follows*(s,c)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("procedure synonym as second arg") {
		std::string queryString = "stmt s; procedure p; Select s such that Follows*(s,p)";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}
}

TEST_CASE("Follows* - missing open paran") {
	std::string queryString = "stmt s; select s such that Follows* s, 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Follows* - missing first") {
	std::string queryString = "stmt s; select s such that Follows* (, 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Follows* - missing comma") {
	std::string queryString = "stmt s; select s such that Follows* (s 1)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Follows* - missing second arg") {
	std::string queryString = "stmt s; select s such that Follows* (s, )";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Follows* - missing close paran") {
	std::string queryString = "stmt s; select s such that Follows* (s, 1";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("Follows* - insufficient arguments") {
	std::string queryString = "stmt s; Select s such that Follows*(s)";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}