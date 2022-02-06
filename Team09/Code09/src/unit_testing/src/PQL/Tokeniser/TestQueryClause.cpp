#include "catch.hpp"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL tokeniser query clause test case 1 : such that + relationship clause 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select w such\t that  Parent*(1,w)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PARENT_T));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 2 : such that + relationship clause 2") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select ifs such\t that  Parent(1,ifs)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "ifs"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PARENT));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "ifs"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 3 : such that + relationship clause 3") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select v such\t that  Uses(1,v)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::USES));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 4 : such that + relationship clause 4") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select v such\t that  Modifies(1,v)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::MODIFIES));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "v"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}


TEST_CASE("PQL tokeniser query clause test case 5 : such that + pattern clause 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"23\")";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PATTERN));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 6 : such that + pattern clause 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"VAR\")";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PATTERN));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "VAR"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 7 : pattern clause and query clause 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"23\") Parent*(1,w)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PATTERN));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::PARENT_T));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 7 : pattern clause and query clause 2") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"23\") Follows*(1, 2)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PATTERN));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::FOLLOWS_T));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "2"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser query clause test case 8 : pattern clause and query clause 3") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "Select a such\t that  pattern a(_, _ \"23\") Follows(1, s)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SELECT));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SUCH));
	expectedPQLTokens.push_back(PQLToken(TokenType::THAT));
	expectedPQLTokens.push_back(PQLToken(TokenType::PATTERN));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "a"));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::UNDERSCORE));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "23"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::FOLLOWS));
	expectedPQLTokens.push_back(PQLToken(TokenType::OPEN_PARAN));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "1"));
	expectedPQLTokens.push_back(PQLToken(TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "s"));
	expectedPQLTokens.push_back(PQLToken(TokenType::CLOSE_PARAN));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}