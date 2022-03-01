#include "catch.hpp"
#include "PQL/Tokeniser.h"
#include "TestingUtils.cpp"

TEST_CASE("PQL tokeniser declaration statement test case 1: single declaration, statement") {
	std::string queryString = "stmt s;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::STMT, "stmt"),
		new PQLToken(TokenType::SYNONYM, "s"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 2: single declaration, print + valid synonym") {
	std::string queryString = "print pn123;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PRINT, "print"),
		new PQLToken(TokenType::SYNONYM, "pn123"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 3: single declaration, while + keyword") {
	std::string queryString = "while Select;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::WHILE, "while"),
		new PQLToken(TokenType::SELECT, "Select"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//Tokeniser will still pass this test case because tokeniser is only concern about the lexical rules of each token from the input, not the syntax of the input 
TEST_CASE("PQL tokeniser declaration statement test case 4: single declaration, variable + integer") {
	std::string queryString = "variable 123;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::VARIABLE, "variable"),
		new PQLToken(TokenType::INTEGER, "123"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 5: double declaration, constant + 2 synonyms") {
	std::string queryString = "constant c1,c2;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CONST, "constant"),
		new PQLToken(TokenType::SYNONYM, "c1"),
		new PQLToken(TokenType::COMMA, ","),
		new PQLToken(TokenType::SYNONYM, "c2"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 6: multi declaration, read + 3 synonyms") {
	std::string queryString = "read r1,r2 , r3;";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::READ, "read"),
		new PQLToken(TokenType::SYNONYM, "r1"),
		new PQLToken(TokenType::COMMA, ","),
		new PQLToken(TokenType::SYNONYM, "r2"),
		new PQLToken(TokenType::COMMA, ","),
		new PQLToken(TokenType::SYNONYM, "r3"),
		new PQLToken(TokenType::SEMICOLON, ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

