#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/Tokeniser.h"

TEST_CASE("With - 2nd arg is string") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("1st arg is string") {
		std::string queryString = "stmt s; Select s with \"v\"=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is int") {
		std::string queryString = "stmt s; Select s with 1=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrref - call.procname") {
		std::string queryString = "call c; Select c with c.procName=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("c"), EntityType::CALL));
		clauseArgs.push_back(QueryArgument(std::string("c"), EntityType::CALL, AttributeRef::PROC_NAME));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		usedSynonyms.insert("c");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));
		

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));

	}

	SECTION("1st arg is attrRef - procedure.procname") {
		std::string queryString = "procedure p; Select p with p.procName=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("p"), EntityType::PROC));
		clauseArgs.push_back(QueryArgument(std::string("p"), EntityType::PROC, AttributeRef::PROC_NAME));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		usedSynonyms.insert("p");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));


		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - variable.varname") {
		std::string queryString = "variable v; Select v with v.varName=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR, AttributeRef::VAR_NAME));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		usedSynonyms.insert("v");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));


		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - read.varname") {
		std::string queryString = "read rd; Select rd with rd.varName=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("rd"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("rd"), EntityType::READ, AttributeRef::VAR_NAME));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		usedSynonyms.insert("rd");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));


		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - print.varName") {
		std::string queryString = "print pn; Select pn with pn.varName=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT, AttributeRef::VAR_NAME));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::STRING));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));


		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - constant.value") {
		std::string queryString = "constant c; Select c with c.value=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - stmt.stmt#") {
		std::string queryString = "stmt s; Select s with s.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - read.stmt#") {
		std::string queryString = "read rd; Select rd with rd.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - print.stmt#") {
		std::string queryString = "print pn; Select pn with pn.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - call.stmt#") {
		std::string queryString = "call c; Select c with c.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - while.stmt#") {
		std::string queryString = "while w; Select w with w.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - if.stmt#") {
		std::string queryString = "if ifs; Select ifs with ifs.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - assign.stmt#") {
		std::string queryString = "assign a; Select a with a.stmt#=\"v\"  ";
		Tokeniser tokeniser = Tokeniser(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

}
 
