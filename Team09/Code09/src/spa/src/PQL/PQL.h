#pragma once 
#include <vector>
#include <models/Query.h>

enum class TokenType {
	//Lexical tokens
	SYNONYM,
	INTEGER,
	STRING,
	WILD, //underscore

	//Puncuation tokens
	SEMICOLON,
	OPEN_PARAN,
	CLOSE_PARAN,
	COMMA,

	//Design-entity tokens
	STMT,
	READ,
	PRINT,
	WHILE,
	IF,
	ASSIGN,
	VARIABLE,
	CONSTANT,
	PROC,

	//Such that clause tokens
	SUCH_THAT,

	//Relationship clause tokens
	MODIFIES,
	USES,
	PARENT,
	PARENT_T,
	FOLLOWS,
	FOLLOWS_T

};

struct PQLToken {
	TokenType type;
	std::string value;
	//overloaded == operator to compare other PQLToken
	bool operator==(const PQLToken& other) const {
		return type == other.type && value == other.value;
	}
	//default constructor
	PQLToken() { type = TokenType::STRING; value = ""; }
	//parameterised constructor
	PQLToken(TokenType tokenType, std::string tokenValue = "") { type = tokenType; value = tokenValue; }
};

namespace PQL {
	/**
	 * @brief	Tokenises a string into a vector of tokens
	 * Tokenising is done by splitting the query string by whitespaces or before/after special characters.
	 * An exception will be thrown if PQL is lexically incorrect 
	 * @param	query String which ontains the PQL query/queries
	 * @return	vector of tokens which will be passed into the parser for parsing
	*/
	const std::vector<PQLToken>& tokenise(std::string query);

	/**
	 * @brief	Parses a vector of tokens into a Query object
	 * @param	tokens Vector of tokens 
	 * @return	Query object to be passed to the evaluator
	*/
	Query parse(std::vector<PQLToken>& tokens);

}