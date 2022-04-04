#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("multiple declared synonyms") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("Duplicated declarations in same entity declaration ") {
		std::string queryString = "stmt s,s; Select s ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}

	SECTION("Duplicated declarations in same entity declaration ") {
		std::string queryString = "stmt s; variable s; Select s ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}
}

TEST_CASE("undeclared synonyms") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("undeclared synonym") {
		std::string queryString = "stmt s1; Select s ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}

	SECTION("undeclared synonym with attr Ref") {
		std::string queryString = "stmt s1; Select s.procName ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}
}

TEST_CASE("synonym attr ref mismatch") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("undeclared synonym with attr Ref") {
		std::string queryString = "stmt s; Select s.procName ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}

	SECTION("undeclared synonym with attr Ref") {
		std::string queryString = "stmt s; Select s.varName ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}

	SECTION("undeclared synonym with attr Ref") {
		std::string queryString = "variable v; Select v.stmt#";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE((actualQuery.isEmpty() && actualQuery.isSemanticErrorDetected()));
	}
}
