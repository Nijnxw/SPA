#include "catch.hpp"
#include "PQL/PQLLexer.h"
#include "TestingUtils.cpp"

TEST_CASE("PQL tokeniser query clause test case 1 : such that + parent_T clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select w such\t that  Parent*(1,w)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PARENT_T, "Parent*"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN, "("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN, ")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 2 : such that + parent clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select ifs such that  Parent(1,_)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "ifs"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PARENT, "Parent"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN, "("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN, ")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 3 : such that + follows clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select v such\t that  Follows(v,1)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::FOLLOWS, "Follows"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN, "("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN, ")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 4 : such that + follows_T clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select v such\t that  Follows*(v,_)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::FOLLOWS_T, "Follows*"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 5 : such that + Modifies clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select v such\t that  Modifies(1,v)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::MODIFIES, "Modifies"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 6 : such that + Uses clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select zv such\t that  Uses(zv,\"proc\")";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "zv"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::USES, "Uses"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "zv"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "proc"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}



TEST_CASE("PQL tokeniser query clause test case 7 : such that + pattern clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"23\"_)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PATTERN, "pattern"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 8 : such that + pattern clause") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(\"proc\", \"VAR\")";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PATTERN, "pattern"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "proc"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "VAR"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 9 : pattern clause and query clause 1") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(b, \"23\") Parent*(_,_)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PATTERN, "pattern"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM,"b"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PARENT_T, "Parent*"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 10 : pattern clause and query clause 2") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _) Follows*(1, 2)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PATTERN, "pattern"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::FOLLOWS_T, "Follows*"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "2"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 8 : pattern clause and query clause 3") {
	std::vector<PQLToken*> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, \"23\") Uses(1, s)";
	PQLLexer tokeniser = PQLLexer(queryString);

	expectedPQLTokens.push_back(new PQLToken(TokenType::SELECT, "Select"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SUCH, "such"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::THAT, "that"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::PATTERN, "pattern"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::UNDERSCORE, "_"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::USES, "Uses"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::OPEN_PARAN,"("));
	expectedPQLTokens.push_back(new PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::COMMA, ","));
	expectedPQLTokens.push_back(new PQLToken(TokenType::SYNONYM, "s"));
	expectedPQLTokens.push_back(new PQLToken(TokenType::CLOSE_PARAN,")"));

	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}