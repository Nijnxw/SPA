#include "catch.hpp"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL tokeniser lexical tokens test case 1 : synonyms with various whitespace") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "these\nare synonyms\ttoo"; 
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("these", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("are", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("synonyms", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("too", TokenType::SYNONYM));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser lexical tokens test case 2 : integers with various whitespaces") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "123\n456 789\t0";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("123", TokenType::INTEGER));
	expectedPQLTokens.push_back(PQLToken("456", TokenType::INTEGER));
	expectedPQLTokens.push_back(PQLToken("789", TokenType::INTEGER));
	expectedPQLTokens.push_back(PQLToken("0", TokenType::INTEGER));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser lexical tokens test case 3 : strings with various white spaces") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "\"these\"\n\"are\" \"strings\"\t\"too\"";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("these", TokenType::STRING));
	expectedPQLTokens.push_back(PQLToken("are", TokenType::STRING));
	expectedPQLTokens.push_back(PQLToken("strings", TokenType::STRING));
	expectedPQLTokens.push_back(PQLToken("too", TokenType::STRING));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser lexical tokens test case 4 : strings with illegal characters") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "\"this^is^illegal\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	REQUIRE_THROWS(tokeniser.tokenise());
}

TEST_CASE("PQL tokeniser lexical tokens test case 5 : illegal ident") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "123thisisillegal";
	Tokeniser tokeniser = Tokeniser(queryString);
	REQUIRE_THROWS(tokeniser.tokenise());
}

TEST_CASE("PQL tokeniser lexical tokens test case 6 : illegal integer") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "123^456";
	Tokeniser tokeniser = Tokeniser(queryString);
	REQUIRE_THROWS(tokeniser.tokenise());
}

TEST_CASE("PQL tokeniser lexical tokens test case 7 : illegal string 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "\"123456asdf\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	REQUIRE_THROWS(tokeniser.tokenise());
}

TEST_CASE("PQL tokeniser lexical tokens test case 8 : illegal string 2") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "\"as,df\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	REQUIRE_THROWS(tokeniser.tokenise());
}