#include "catch.hpp"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL tokeniser lexical tokens test case 1 : synonyms with various whitespace") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "these\nare synonyms\ttoo"; 
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM,"these"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "are"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "synonyms"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "too")) ;

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser lexical tokens test case 2 : integers with various whitespaces") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "123\n456 789\t0";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "123"));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "456"));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "789"));
	expectedPQLTokens.push_back(PQLToken(TokenType::INTEGER, "789"));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser lexical tokens test case 3 : strings with various white spaces") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "\"these\"\n\"are\" \"strings\"\t\"too\"";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "these"));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "are"));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "strings"));
	expectedPQLTokens.push_back(PQLToken(TokenType::STRING, "too"));

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