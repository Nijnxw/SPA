#pragma once

#include <vector>
#include <list>
#include "models/Query.h"
#include "models/QueryClauseTable.h""
#include "PQL/PQLToken.h"

namespace PQL {
	/**
	 * @brief	Tokenises a string into a vector of tokens
	 * Tokenising is done by splitting the query string by whitespaces or before/after special characters.
	 * An exception will be thrown if PQL is lexically incorrect 
	 * @param	query String which ontains the PQL query/queries
	 * @return	vector of tokens which will be passed into the parser for parsing
	*/
	const std::vector<PQLToken*> tokenise(std::string query);

	/**
	 * @brief	Parses a vector of tokens into a Query object
	 * @param	tokens Vector of tokens 
	 * @return	Query object to be passed to the evaluator
	 */
	Query parse(std::vector<PQLToken*> tokens);

	Table evaluate(Query& query);

	std::unordered_set<std::string> getResults(Table& res, std::vector<QueryArgument>& selectSyn);

}