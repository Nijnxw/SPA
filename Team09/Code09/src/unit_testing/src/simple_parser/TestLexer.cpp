#include "simple_parser/Token.h"
#include "simple_parser/Lexer.h"

#include "catch.hpp"
#include <sstream>

bool tokenComparator(const Token* t1, const Token* t2) {
    return t1->type == t2->type && t1->value == t2->value;
}

bool compareVectors(const std::vector<Token*> output, const std::vector<Token*> expected) {
    return std::equal(output.begin(), output.end(),
                      expected.begin(), expected.end(),
                      tokenComparator);
}

// --------------------------------------------------
//                  HAPPY PATHS
// --------------------------------------------------

TEST_CASE("Test end of file token") {
    std::string program = "";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = { new EndOfFileToken() };

    REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test name tokens") {
    std::string program = "procedure     ProCedure if read x1 X1 x1x x1X x";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = {
        new NameToken("procedure"), new NameToken("ProCedure"),
        new NameToken("if"),        new NameToken("read"),
        new NameToken("x1"),        new NameToken("X1"),
        new NameToken("x1x"),       new NameToken("x1X"),
        new NameToken("x"),         new EndOfFileToken(),
    };

    REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test integer tokens") {
    std::string program = "1 13  093";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = {
            new IntegerToken("1"),     new IntegerToken("13"),
            new IntegerToken("093"),   new EndOfFileToken(),
    };

    REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test symbol tokens") {
    std::string program = "{ ) + && = ! != < >=";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = {
            new SymbolToken("{"),   new SymbolToken(")"),
            new SymbolToken("+"),   new SymbolToken("&&"),
            new SymbolToken("="),   new SymbolToken("!"),
            new SymbolToken("!="),  new SymbolToken("<"),
            new SymbolToken(">="),  new EndOfFileToken(),
    };

    REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test all lexical tokens") {
    std::string program = "if while procedure ( ) { } && variAble ball8 89 2 < <= = != print V1 v1e";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = {
            new NameToken("if"),        new NameToken("while"),
            new NameToken("procedure"), new SymbolToken("("),
            new SymbolToken(")"),       new SymbolToken("{"),
            new SymbolToken("}"),       new SymbolToken("&&"),
            new NameToken("variAble"),  new NameToken("ball8"),
            new IntegerToken("89"),     new IntegerToken("2"),
            new SymbolToken("<"),       new SymbolToken("<="),
            new SymbolToken("="),       new SymbolToken("!="),
            new NameToken("print"),     new NameToken("V1"),
            new NameToken("v1e"),       new EndOfFileToken(),
    };

    REQUIRE(compareVectors(output, expected));
}

TEST_CASE("Test SIMPLE program") {
    std::string program = R"(
    procedure sumDigits {
        read number;
        sum = 0;

        while (number > 0) {
            digit = number % 10;
            sum = sum + digit;
            number = number / 10;
        }

        print sum;
    }
    )";
    std::istringstream input(program);

    auto lexer = Lexer(&input);
    std::vector<Token*> output = lexer.tokenize();
    std::vector<Token*> expected = {
            new NameToken("procedure"),     new NameToken("sumDigits"),     new SymbolToken("{"),
            new NameToken("read"),          new NameToken("number"),        new SymbolToken(";"),
            new NameToken("sum"),           new SymbolToken("="),           new IntegerToken("0"),
            new SymbolToken(";"),           new NameToken("while"),         new SymbolToken("("),
            new NameToken("number"),        new SymbolToken(">"),           new IntegerToken("0"),
            new SymbolToken(")"),           new SymbolToken("{"),           new NameToken("digit"),
            new SymbolToken("="),           new NameToken("number"),        new SymbolToken("%"),
            new IntegerToken("10"),         new SymbolToken(";"),           new NameToken("sum"),
            new SymbolToken("="),           new NameToken("sum"),           new SymbolToken("+"),
            new NameToken("digit"),         new SymbolToken(";"),           new NameToken("number"),
            new SymbolToken("="),           new NameToken("number"),        new SymbolToken("/"),
            new IntegerToken("10"),         new SymbolToken(";"),           new SymbolToken("}"),
            new NameToken("print"),         new NameToken("sum"),           new SymbolToken(";"),
            new SymbolToken("}"),           new EndOfFileToken(),
    };

    REQUIRE(compareVectors(output, expected));
}

// --------------------------------------------------
//                  UNHAPPY PATHS
// --------------------------------------------------
TEST_CASE("Test undefined tokens") {
    std::string program = "@";
    std::istringstream input(program);
    auto lexer = Lexer(&input);
    REQUIRE_THROWS(lexer.tokenize());
}

TEST_CASE("Test next token is incorrect") {
    SECTION("& token") {
        std::string program = "&2";
        std::istringstream input(program);
        auto lexer = Lexer(&input);
        REQUIRE_THROWS(lexer.tokenize());
    }

    SECTION("| token") {
        std::string program = "|>";
        std::istringstream input(program);
        auto lexer = Lexer(&input);
        REQUIRE_THROWS(lexer.tokenize());
    }
}