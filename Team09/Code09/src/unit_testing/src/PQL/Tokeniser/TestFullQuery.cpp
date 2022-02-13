#include "catch.hpp"
#include "PQL/Tokeniser.h"

TEST_CASE("PQL tokeniser full query test case 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "while w;Select w such\t that  Parent*(1,w)";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken(TokenType::WHILE));
	expectedPQLTokens.push_back(PQLToken(TokenType::SYNONYM, "w"));
	expectedPQLTokens.push_back(PQLToken(TokenType::SEMICOLON));
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
