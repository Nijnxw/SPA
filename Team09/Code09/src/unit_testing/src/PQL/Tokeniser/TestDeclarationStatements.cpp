#include "catch.hpp"
#include "PQL\Tokeniser.h"

TEST_CASE("PQL tokeniser declaration statement test case 1: statement") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "stmt s;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::STMT));
	expectedPQLTokens.push_back(PQLToken("s", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 2: read") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "read rd;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::READ));
	expectedPQLTokens.push_back(PQLToken("rd", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 3: print") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "read rd;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::READ));
	expectedPQLTokens.push_back(PQLToken("rd", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 4: while") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "while w;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::WHILE));
	expectedPQLTokens.push_back(PQLToken("w", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 5: if") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "if ifs;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::IF));
	expectedPQLTokens.push_back(PQLToken("ifs", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 6: assign") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "assign a;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::ASSIGN));
	expectedPQLTokens.push_back(PQLToken("a", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 7: variable") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "variable v;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::VARIABLE));
	expectedPQLTokens.push_back(PQLToken("v", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 8: constant") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "constant c;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::CONST));
	expectedPQLTokens.push_back(PQLToken("c", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 9: procedure") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "procedure proc;";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::PROC));
	expectedPQLTokens.push_back(PQLToken("proc", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 10: multiple declarations 1") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "procedure proc; constant c,c1;\nvariable v,v1; ";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::PROC));
	expectedPQLTokens.push_back(PQLToken("proc", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	expectedPQLTokens.push_back(PQLToken("", TokenType::CONST));
	expectedPQLTokens.push_back(PQLToken("c", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken("c1", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	expectedPQLTokens.push_back(PQLToken("", TokenType::VARIABLE));
	expectedPQLTokens.push_back(PQLToken("v", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken("v1", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser declaration statement test case 11: multiple declarations 2") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "assign a; while w,w1;\nif ifs,ifs1; ";
	Tokeniser tokeniser = Tokeniser(queryString);

	expectedPQLTokens.push_back(PQLToken("", TokenType::ASSIGN));
	expectedPQLTokens.push_back(PQLToken("a", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	expectedPQLTokens.push_back(PQLToken("", TokenType::WHILE));
	expectedPQLTokens.push_back(PQLToken("w", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken("w1", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	expectedPQLTokens.push_back(PQLToken("", TokenType::IF));
	expectedPQLTokens.push_back(PQLToken("ifs", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::COMMA));
	expectedPQLTokens.push_back(PQLToken("ifs1", TokenType::SYNONYM));
	expectedPQLTokens.push_back(PQLToken("", TokenType::SEMICOLON));

	std::vector<PQLToken> PQLTokens = tokeniser.tokenise();

	bool result = std::equal(PQLTokens.begin(), PQLTokens.end(), expectedPQLTokens.begin());
	REQUIRE(result);
}


TEST_CASE("PQL tokeniser declaration statement test case 12: incorrect declaration") {
	std::vector<PQLToken> expectedPQLTokens;
	std::string queryString = "as^sign a; while w,w1;\nif ifs,ifs1; ";
	Tokeniser tokeniser = Tokeniser(queryString);

	REQUIRE_THROWS(tokeniser.tokenise());
}