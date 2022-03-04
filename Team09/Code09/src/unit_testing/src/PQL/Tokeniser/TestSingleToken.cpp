#include "catch.hpp"
#include "PQL/Tokeniser.h"
#include "TestingUtils.cpp"

//----------------------------------------------------------------//
//							HAPPY PATHS						      //
//----------------------------------------------------------------//

//---------------------------------//
//	    design enitiy tokens       //
//---------------------------------//

TEST_CASE("PQL Tokeniser individual token test case 1: statement") {
	std::string queryString = "stmt";
	auto tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> actualPQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::STMT, "stmt")
	};

	bool result = compareVectors(actualPQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 2: read") {
	std::string queryString = "read";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::READ, "read")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 3: print") {
	std::string queryString = "print";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PRINT, "print")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token  test case 4: while") {
	std::string queryString = "while";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::WHILE, "while")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 5: if") {
	std::string queryString = "if";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::IF, "if")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 6: assign") {
	std::string queryString = "assign";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::ASSIGN, "assign")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 7: variable") {
	std::string queryString = "variable";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::VARIABLE, "variable")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 8: constant") {
	std::string queryString = "constant";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CONST, "constant")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 9: procedure") {
	std::string queryString = "procedure";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PROC, "procedure")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 36: call") {
	std::string queryString = "call";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CALL, "call")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	     suchthat-cl tokens        //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 10: such") {
	std::string queryString = "such";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::SUCH, "such")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 11: that") {
	std::string queryString = "that";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::THAT, "that")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 12: Follows") {
	std::string queryString = "Follows";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::FOLLOWS, "Follows")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 13: Follows*") {
	std::string queryString = "Follows*";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::FOLLOWS_T, "Follows*")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 14: Parent") {
	std::string queryString = "Parent";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PARENT, "Parent")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 15: Parent*") {
	std::string queryString = "Parent*";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PARENT_T, "Parent*")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 16: Uses") {
	std::string queryString = "Uses";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::USES, "Uses")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 17: Modifies") {
	std::string queryString = "Modifies";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::MODIFIES, "Modifies")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 37: Calls") {
	std::string queryString = "Calls";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CALLS, "Calls")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 38: Calls*") {
	std::string queryString = "Calls*";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CALLS_T, "Calls*")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 39: Next") {
	std::string queryString = "Next";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::NEXT, "Next")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 40: Next*") {
	std::string queryString = "Next*";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::NEXT_T, "Next*")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 39: Affects") {
	std::string queryString = "Affects";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::AFFECTS, "Affects")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 40: Affects*") {
	std::string queryString = "Affects*";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::AFFECTS_T, "Affects*")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}


//---------------------------------//
//	      pattern-cl tokens        //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 18: pattern") {
	std::string queryString = "pattern";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PATTERN, "pattern")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	      puncuator tokens         //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 19: open paranthesis") {
	std::string queryString = "(";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::OPEN_PARAN, "(")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 20: close paranthesis") {
	std::string queryString = ")";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CLOSE_PARAN, ")")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 41: open angled") {
	std::string queryString = "<";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::OPEN_ANGLED, "<")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 42: close angled") {
	std::string queryString = ">";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::CLOSE_ANGLED, ">")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 21: comma") {
	std::string queryString = ",";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::COMMA, ",")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 22: semi-colon") {
	std::string queryString = ";";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::SEMICOLON,  ";")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 23: underscore") {
	std::string queryString = "_";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::UNDERSCORE, "_")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 43: period") {
	std::string queryString = ".";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::PERIOD, ".")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	        select tokens          //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 24: select") {
	std::string queryString = "Select";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::SELECT, "Select")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 44: boolean") {
	std::string queryString = "BOOLEAN";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::BOOLEAN, "BOOLEAN")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	        with clause            //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 45: with") {
	std::string queryString = "with";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::WITH, "with")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 46: =") {
	std::string queryString = "=";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::EQUAL, "=")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//				and		           //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 46: and") {
	std::string queryString = "and";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::AND, "and")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	        integer tokens         //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 25: integer") {
	std::string queryString = "0123456789";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::INTEGER, "0123456789")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//---------------------------------//
//	        synonym tokens         //
//---------------------------------//

TEST_CASE("PQL tokeniser individual token test case 26: synonym letters only") {
	std::string queryString = "w";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::SYNONYM, "w")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 26: synonym letters + digits") {
	std::string queryString = "w1";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::SYNONYM, "w1")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 27: string letters only") {
	std::string queryString = "\"TESTING\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::STRING, "TESTING")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

TEST_CASE("PQL tokeniser individual token test case 28: string letters + digits") {
	std::string queryString = "\"TESTING\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::STRING, "TESTING")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}


TEST_CASE("PQL tokeniser individual token test case 29: factor (string) digits") {
	std::string queryString = "\"1234\"";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();

	std::vector<PQLToken*> expectedPQLTokens = {
		new PQLToken(TokenType::STRING, "1234")
	};

	bool result = compareVectors(PQLTokens, expectedPQLTokens);
	REQUIRE(result);
}

//----------------------------------------------------------------//
//							UNHAPPY PATHS						  //
//----------------------------------------------------------------//


TEST_CASE("PQL tokeniser individual token test case 34: invalid ident (punctuator present)") {
	std::string queryString = "q@werty";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> tokens = tokeniser.tokenise();
	REQUIRE(tokens.empty());
}

TEST_CASE("PQL tokeniser individual token test case 35: symbols not in list of allowed symbols") {
	std::string queryString = "@";
	Tokeniser tokeniser = Tokeniser(queryString);
	std::vector<PQLToken*> tokens = tokeniser.tokenise();
	REQUIRE(tokens.empty());
}

