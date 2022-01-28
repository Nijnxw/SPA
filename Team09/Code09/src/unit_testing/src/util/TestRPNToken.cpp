#include "catch.hpp"
#include "../src/util/RPNToken.h"

TEST_CASE("Correct Initialization") {
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::Integer, "1"));
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::Variable, "Test"));
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::Operator, "+"));
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::Operator, "/"));
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::LeftParenthesis, "("));
    REQUIRE_NOTHROW(RPNToken(RPNTokenType::RightParenthesis, ")"));
}

TEST_CASE("Test Getters") {
    RPNToken integerToken(RPNTokenType::Integer, "1");
    RPNToken variableToken(RPNTokenType::Variable, "Test");
    RPNToken operatorToken(RPNTokenType::Operator, "+");
    RPNToken LeftParenthesisToken(RPNTokenType::LeftParenthesis, "(");
    RPNToken RightParenthesisToken(RPNTokenType::RightParenthesis, ")");

    REQUIRE(integerToken.getContents() == "1");
    REQUIRE(integerToken.getPrecedence() == -1);
    REQUIRE(integerToken.isInteger() == true);
    REQUIRE(integerToken.isVariable() == false);
    REQUIRE(integerToken.isOperator() == false);
    REQUIRE(integerToken.isLeftParenthesis() == false);
    REQUIRE(integerToken.isRightParenthesis() == false);

    REQUIRE(variableToken.getContents() == "Test");
    REQUIRE(variableToken.getPrecedence() == -1);
    REQUIRE(variableToken.isInteger() == false);
    REQUIRE(variableToken.isVariable() == true);
    REQUIRE(variableToken.isOperator() == false);
    REQUIRE(variableToken.isLeftParenthesis() == false);
    REQUIRE(variableToken.isRightParenthesis() == false);

    REQUIRE(operatorToken.getContents() == "+");
    REQUIRE(operatorToken.getPrecedence() == 2);
    REQUIRE(operatorToken.isInteger() == false);
    REQUIRE(operatorToken.isVariable() == false);
    REQUIRE(operatorToken.isOperator() == true);
    REQUIRE(operatorToken.isLeftParenthesis() == false);
    REQUIRE(operatorToken.isRightParenthesis() == false);

    REQUIRE(LeftParenthesisToken.getContents() == "(");
    REQUIRE(LeftParenthesisToken.getPrecedence() == -1);
    REQUIRE(LeftParenthesisToken.isInteger() == false);
    REQUIRE(LeftParenthesisToken.isVariable() == false);
    REQUIRE(LeftParenthesisToken.isOperator() == false);
    REQUIRE(LeftParenthesisToken.isLeftParenthesis() == true);
    REQUIRE(LeftParenthesisToken.isRightParenthesis() == false);

    REQUIRE(RightParenthesisToken.getContents() == ")");
    REQUIRE(RightParenthesisToken.getPrecedence() == -1);
    REQUIRE(RightParenthesisToken.isInteger() == false);
    REQUIRE(RightParenthesisToken.isVariable() == false);
    REQUIRE(RightParenthesisToken.isOperator() == false);
    REQUIRE(RightParenthesisToken.isLeftParenthesis() == false);
    REQUIRE(RightParenthesisToken.isRightParenthesis() == true);
}

TEST_CASE("Test Operator Comparison") {
    RPNToken plusToken(RPNTokenType::Operator, "+");
    RPNToken minusToken(RPNTokenType::Operator, "-");
    RPNToken multiplyToken(RPNTokenType::Operator, "*");
    RPNToken divideToken(RPNTokenType::Operator, "/");

    REQUIRE(plusToken.comparePrecedence(minusToken) == 0);
    REQUIRE(plusToken.comparePrecedence(multiplyToken) == -1);
    REQUIRE(multiplyToken.comparePrecedence(minusToken) == 1);
    REQUIRE(divideToken.comparePrecedence(multiplyToken) == 0);
}

TEST_CASE("Test Invalid Operator") {
    REQUIRE_THROWS_WITH(RPNToken(RPNTokenType::Operator, "aa"), "Invalid Token Content.\n");
}
