#include "catch.hpp"
#include "../src/util/RPN.h"

TEST_CASE("Correct Handling of Single Numbers") {
    REQUIRE(RPN::convertToRpn("1") == "1");
    REQUIRE(RPN::convertToRpn("999") == "999");
}

TEST_CASE("Correct Handling of Variables") {
    REQUIRE(RPN::convertToRpn("a") == "a");
    REQUIRE(RPN::convertToRpn("xyz") == "xyz");
}

TEST_CASE("Correct Handling of Expressions") {
    REQUIRE(RPN::convertToRpn("1+2+3") == "1 2 + 3 +");
    REQUIRE(RPN::convertToRpn("11-2+3") == "11 2 - 3 +");
    REQUIRE(RPN::convertToRpn("a+b+c") == "a b + c +");
}

TEST_CASE("Correct Handling of Whitespace") {
    std::vector<std::string> expected;

    REQUIRE_THROWS_WITH(RPN::convertToRpn(""), "No tokens Detected.\n");
    REQUIRE_THROWS_WITH(RPN::convertToRpn(" "), "No tokens Detected.\n");
    REQUIRE_THROWS_WITH(RPN::convertToRpn("	"), "No tokens Detected.\n");

    REQUIRE(RPN::convertToRpn("1 + 1") == "1 1 +");
}

TEST_CASE("Correct Handling of Terms") {
    REQUIRE(RPN::convertToRpn("11 * 3 / 1") == "11 3 * 1 /");
    REQUIRE(RPN::convertToRpn("1 * 2 + 3 % 1") == "1 2 * 3 1 % +");
    REQUIRE(RPN::convertToRpn("1 * 22 * 3 + 1") == "1 22 * 3 * 1 +");
    REQUIRE(RPN::convertToRpn("a * b + c / 1") == "a b * c 1 / +");
}

TEST_CASE("Correct Handling of Parentheses") {
    REQUIRE(RPN::convertToRpn("(1 - 5)") == "1 5 -");
    REQUIRE(RPN::convertToRpn("3 + 44 * 2 / ( 1 - 5 )") == "3 44 2 * 1 5 - / +");
    REQUIRE(RPN::convertToRpn("3+4*2/(1-5)+1*22") == "3 4 2 * 1 5 - / + 1 22 * +");
}

TEST_CASE("Correct Handling of Contains") {
    std::string expected;

    //contains itself
    std::string rpn1("3 4 2 * 1 5 - / + 1 22 * +");
    REQUIRE(RPN::contains(rpn1, rpn1) == true);

    std::string rpn2("3 4 2 *");
    std::string rpn3("3 4 *");
    REQUIRE(RPN::contains(rpn1, rpn2) == true);
    REQUIRE(RPN::contains(rpn1, rpn3) == false);
}

TEST_CASE("Invalid Token Name") {
    REQUIRE_THROWS_WITH(RPN::convertToRpn("^% + #$"), "Invalid Token Detected in Statement.\n");
}

TEST_CASE("Mismatch Parentheses") {
    REQUIRE_THROWS_WITH(RPN::convertToRpn("1+)"), "Non Matching Parentheses Detected.\n");
    REQUIRE_THROWS_WITH(RPN::convertToRpn("(abc+123"), "Non Matching Parentheses Detected.\n");
}

TEST_CASE("RPN mismatch size") {
    std::string rpn1("3 4 2 *");
    std::string rpn2("3 4 2 * 1 5 - / + 1 22 * +");
    
    REQUIRE_NOTHROW(RPN::contains(rpn2, rpn1) == true);
    REQUIRE_THROWS_WITH(RPN::contains(rpn1, rpn2), "RPN elements length mismatch.\n");
}
