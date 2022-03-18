#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("missing rel clause") {
	std::string queryString = "variable v; Select v such that  (1,2)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("missing such") {
	std::string queryString = "variable v; Select v that Modifies (1,v)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("missing that") {
	std::string queryString = "variable v; Select v such Modifies (1,v)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}

TEST_CASE("missing such that") {
	std::string queryString = "variable v; Select v Modifies(1, v)";
	PQLLexer tokeniser = PQLLexer(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
	PQLParser parser = PQLParser(PQLTokens);

	Query actualQuery = parser.parse();
	REQUIRE((actualQuery.isEmpty()));
}
