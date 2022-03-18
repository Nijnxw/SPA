#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("With - 2nd arg is string") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("1st arg is string") {
		std::string queryString = "stmt s; Select s with \"v\"=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrref - call.procname") {
		std::string queryString = "call c; Select c with c.procName=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
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
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - stmt.stmt#") {
		std::string queryString = "stmt s; Select s with s.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - read.stmt#") {
		std::string queryString = "read rd; Select rd with rd.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - print.stmt#") {
		std::string queryString = "print pn; Select pn with pn.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - call.stmt#") {
		std::string queryString = "call c; Select c with c.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - while.stmt#") {
		std::string queryString = "while w; Select w with w.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - if.stmt#") {
		std::string queryString = "if ifs; Select ifs with ifs.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - assign.stmt#") {
		std::string queryString = "assign a; Select a with a.stmt#=\"v\"  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

}

TEST_CASE("With - 2nd arg is int") {

	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::unordered_set<std::string> usedSynonyms;

	SECTION("1st arg is string") {
		std::string queryString = "stmt s; Select s with \"v\"=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is int") {
		std::string queryString = "stmt s; Select s with 1=1 ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrref - call.procname") {
		std::string queryString = "call c; Select c with c.procName=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());

	}

	SECTION("1st arg is attrRef - procedure.procname") {
		std::string queryString = "procedure p; Select p with p.procName=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - variable.varname") {
		std::string queryString = "variable v; Select v with v.varName=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - read.varname") {
		std::string queryString = "read rd; Select rd with rd.varName=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - print.varName") {
		std::string queryString = "print pn; Select pn with pn.varName=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();
		REQUIRE(actualQuery.isEmpty());
	}

	SECTION("1st arg is attrRef - constant.value") {
		std::string queryString = "constant c; Select c with c.value=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("c"), EntityType::CONST));
		clauseArgs.push_back(QueryArgument(std::string("c"), EntityType::CONST, AttributeRef::VALUE));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("c");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - stmt.stmt#") {
		std::string queryString = "stmt s; Select s with s.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("s"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s"), EntityType::STMT, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("s");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - read.stmt#") {
		std::string queryString = "read rd; Select rd with rd.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("rd"), EntityType::READ));
		clauseArgs.push_back(QueryArgument(std::string("rd"), EntityType::READ, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("rd");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - print.stmt#") {
		std::string queryString = "print pn; Select pn with pn.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("pn"), EntityType::PRINT));
		clauseArgs.push_back(QueryArgument(std::string("pn"), EntityType::PRINT, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("pn");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - call.stmt#") {
		std::string queryString = "call c; Select c with c.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("c"), EntityType::CALL));
		clauseArgs.push_back(QueryArgument(std::string("c"), EntityType::CALL, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("c");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - while.stmt#") {
		std::string queryString = "while w; Select w with w.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("w"), EntityType::WHILE));
		clauseArgs.push_back(QueryArgument(std::string("w"), EntityType::WHILE, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("w");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - if.stmt#") {
		std::string queryString = "if ifs; Select ifs with ifs.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("ifs");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("1st arg is attrRef - assign.stmt#") {
		std::string queryString = "assign a; Select a with a.stmt#=1  ";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN, AttributeRef::STMT_NO));
		clauseArgs.push_back(QueryArgument(std::string("1"), EntityType::INT));
		usedSynonyms.insert("a");
		expectedClauses.push_back(QueryClause(RelationRef::WITH, clauseArgs, usedSynonyms));

		Query actualQuery = parser.parse();
		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(), actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

}
