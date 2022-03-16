#include "catch.hpp"
#include "PQL/PQLParser.h"
#include "PQL/PQLLexer.h"

TEST_CASE("Modifies + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign a; Select a such that Modifies(3,\"var\") pattern a(_,\"x\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("3"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("var"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a");
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		patternArgs.push_back(QueryArgument(std::string("x"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), common var syn") {
		std::string queryString = "assign a1; variable v;Select a1 such that Modifies(4,v) pattern a1(v,\"z\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a1"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("v");
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a1");
		patternUsedSynonyms.insert("v");
		patternArgs.push_back(QueryArgument(std::string("v"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("z"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a1"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (2pattern), no common syn") {
		std::string queryString = "assign a2; variable v1; Select a2 such that Modifies(2,\"c\") pattern a2(v1,\"d\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a2"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("2"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("c"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a2");
		patternUsedSynonyms.insert("v1");
		patternArgs.push_back(QueryArgument(std::string("v1"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("d"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a2"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), common assign syn") {
		std::string queryString = "assign a3; variable v2; Select a3 such that Modifies(a3,v2) pattern a3(\"test2\",\"test1\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a3"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("a3");
		relUsedSynonyms.insert("v2");
		clauseArgs.push_back(QueryArgument(std::string("a3"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v2"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a3");
		patternArgs.push_back(QueryArgument(std::string("test2"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("test1"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a3"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), no common syn") {
		std::string queryString = "assign a4; variable v2,v3; Select a4 such that Modifies(5,v2) pattern a4(v3,\"test3\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a4"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("v2");
		clauseArgs.push_back(QueryArgument(std::string("5"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("v2"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a4");
		patternUsedSynonyms.insert("v3");
		patternArgs.push_back(QueryArgument(std::string("v3"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test3"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a4"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym , 1 common syn on var") {
		std::string queryString = "assign a5,a6; variable v5; Select a5 such that Modifies(a6,v5) pattern a5(v5,\"asdf\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a5"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("a6");
		relUsedSynonyms.insert("v5");
		clauseArgs.push_back(QueryArgument(std::string("a6"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("v5"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a5");
		patternUsedSynonyms.insert("v5");
		patternArgs.push_back(QueryArgument(std::string("v5"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("asdf"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a5"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), 1 common syn on var") {
		std::string queryString = "assign assign; variable var; Select assign such that Modifies(123,var) pattern assign(var,\"y\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("assign"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("var");
		clauseArgs.push_back(QueryArgument(std::string("123"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("var"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("assign");
		patternUsedSynonyms.insert("var");
		patternArgs.push_back(QueryArgument(std::string("var"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("y"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "assign"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Uses + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign as; Select as such that Uses(13,\"variable\") pattern as(\"b\",\"a\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("as"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("13"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("variable"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::USES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("as");
		patternArgs.push_back(QueryArgument(std::string("b"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("a"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "as"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), NO common syn") {
		std::string queryString = "assign an; variable vd; Select an such that Uses(15,\"Cout\") pattern an(vd,\"Cx\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("an"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("15"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("Cout"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::USES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("an");
		patternUsedSynonyms.insert("vd");
		patternArgs.push_back(QueryArgument(std::string("vd"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("Cx"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "an"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), No common syn") {
		std::string queryString = "assign x1, x2; variable y1; Select x1 such that Uses(x1,y1) pattern x2(\"piece\",\"cost\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("x1"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("x1");
		relUsedSynonyms.insert("y1");
		clauseArgs.push_back(QueryArgument(std::string("x1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("y1"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::USES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("x2");
		patternArgs.push_back(QueryArgument(std::string("piece"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("cost"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "x2"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), common assign syn") {
		std::string queryString = "assign x3; variable y2,y3; Select x3 such that Uses(x3,y2) pattern x3(y3,\"test3\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("x3"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("x3");
		relUsedSynonyms.insert("y2");
		clauseArgs.push_back(QueryArgument(std::string("x3"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("y2"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::USES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("x3");
		patternUsedSynonyms.insert("y3");
		patternArgs.push_back(QueryArgument(std::string("y3"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test3"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "x3"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym, common var syn") {
		std::string queryString = "assign as1,as2; variable vr2; Select as1 such that Modifies(as1,vr2) pattern as2(vr2,\"e\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("as1"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("as1");
		relUsedSynonyms.insert("vr2");
		clauseArgs.push_back(QueryArgument(std::string("as1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("vr2"), EntityType::VAR));
		expectedClauses.push_back(QueryClause(RelationRef::MODIFIES, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("as2");
		patternUsedSynonyms.insert("vr2");
		patternArgs.push_back(QueryArgument(std::string("vr2"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("e"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "as2"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Follows + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign pattern; Select pattern such that Follows(14,15) pattern pattern(_,_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("pattern"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("14"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("15"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("pattern");
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "pattern"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), common assign syn") {
		std::string queryString = "assign while; Select while such that Follows(while,16) pattern while(\"jb\",\"Cnp\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("while"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("while");
		clauseArgs.push_back(QueryArgument(std::string("while"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("16"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("while");
		patternArgs.push_back(QueryArgument(std::string("jb"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("Cnp"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "while"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (2 pattern), no common syn") {
		std::string queryString = "assign variable; variable stmt ;Select variable such that Follows(17,18) pattern variable(stmt,\"jp\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("variable"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("17"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("18"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("variable");
		patternUsedSynonyms.insert("stmt");
		patternArgs.push_back(QueryArgument(std::string("stmt"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("jp"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "variable"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), No common syn") {
		std::string queryString = "assign if, print, van;  Select if such that Follows(if,van) pattern print(\"lom\",\"bind\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("if"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("if");
		relUsedSynonyms.insert("van");

		clauseArgs.push_back(QueryArgument(std::string("if"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("van"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("print");

		patternArgs.push_back(QueryArgument(std::string("lom"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("bind"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "print"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), common assign syn") {
		std::string queryString = "assign asn, asn1; variable d2; Select asn such that Follows(asn,12) pattern asn(d2,\"test4\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("asn"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("asn");
		clauseArgs.push_back(QueryArgument(std::string("asn"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("12"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("asn");
		patternUsedSynonyms.insert("d2");
		patternArgs.push_back(QueryArgument(std::string("d2"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test4"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "asn"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym, common assign syn") {
		std::string queryString = "assign as1,as2; variable vr4; Select as1 such that Follows(as1,as2) pattern as1(vr4,\"e\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("as1"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("as1");
		relUsedSynonyms.insert("as2");
		clauseArgs.push_back(QueryArgument(std::string("as1"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("as2"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("as1");
		patternUsedSynonyms.insert("vr4");
		patternArgs.push_back(QueryArgument(std::string("vr4"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("e"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "as1"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Follows* + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign constant; Select constant such that Follows*(24,35) pattern constant(_,_\"value\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("constant"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("24"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("35"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("constant");
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		patternArgs.push_back(QueryArgument(std::string("_value_"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "constant"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), common assign syn") {
		std::string queryString = "assign read; Select read such that Follows*(read,26) pattern read(\"jn\",\"jnp\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("read"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("read");
		clauseArgs.push_back(QueryArgument(std::string("read"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("26"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("read");
		patternArgs.push_back(QueryArgument(std::string("jn"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("jnp"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "read"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), common assign syn") {
		std::string queryString = "assign Follows, vat;  Select Follows such that Follows*(Follows,vat) pattern Follows(\"msg\",\"msg2\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("Follows"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("Follows");
		relUsedSynonyms.insert("vat");

		clauseArgs.push_back(QueryArgument(std::string("Follows"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("vat"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("Follows");

		patternArgs.push_back(QueryArgument(std::string("msg"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("msg2"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "Follows"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), no common syn") {
		std::string queryString = "assign asn2, asn3; variable d24; Select asn2 such that Follows*(asn2,22) pattern asn3(d24,\"test24\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("asn2"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("asn2");
		clauseArgs.push_back(QueryArgument(std::string("asn2"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("22"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("asn3");
		patternUsedSynonyms.insert("d24");
		patternArgs.push_back(QueryArgument(std::string("d24"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test24"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "asn3"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym, common assign syn") {
		std::string queryString = "assign asm,asc; variable vr24; Select asm such that Follows*(asm,asc) pattern asm(vr24,\"tel\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("asm"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("asm");
		relUsedSynonyms.insert("asc");
		clauseArgs.push_back(QueryArgument(std::string("asm"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("asc"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::FOLLOWS_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("asm");
		patternUsedSynonyms.insert("vr24");
		patternArgs.push_back(QueryArgument(std::string("vr24"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("tel"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "asm"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Parent + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign such; Select such such that Parent(124,135) pattern such(_,_\"cost\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("such"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("124"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("135"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("such");
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		patternArgs.push_back(QueryArgument(std::string("_cost_"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "such"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), common assign syn") {
		std::string queryString = "assign constant; Select constant such that Parent(constant,26) pattern constant(\"jne\",\"jep\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("constant"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("constant");
		clauseArgs.push_back(QueryArgument(std::string("constant"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("26"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("constant");
		patternArgs.push_back(QueryArgument(std::string("jne"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("jep"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "constant"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), common assign syn") {
		std::string queryString = "assign Parent, vm;  Select Parent such that Parent(Parent,vm) pattern Parent(\"msg\",\"msg2\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("Parent"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("Parent");
		relUsedSynonyms.insert("vm");

		clauseArgs.push_back(QueryArgument(std::string("Parent"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("vm"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("Parent");

		patternArgs.push_back(QueryArgument(std::string("msg"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("msg2"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "Parent"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), no common syn") {
		std::string queryString = "assign ab2; variable x24; if ifs; Select ab2 such that Parent(ifs,12) pattern ab2(x24,\"test124\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("ab2"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("ifs");
		clauseArgs.push_back(QueryArgument(std::string("ifs"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("12"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("ab2");
		patternUsedSynonyms.insert("x24");
		patternArgs.push_back(QueryArgument(std::string("x24"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test124"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "ab2"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym, no common syn") {
		std::string queryString = "assign a123,a456; if ifs2; variable vr124; Select a456 such that Parent(ifs2,a123) pattern a456(vr124,\"tele\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a456"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("ifs2");
		relUsedSynonyms.insert("a123");
		clauseArgs.push_back(QueryArgument(std::string("ifs2"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("a123"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a456");
		patternUsedSynonyms.insert("vr124");
		patternArgs.push_back(QueryArgument(std::string("vr124"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("tele"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a456"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}

TEST_CASE("Parent* + pattern") {
	std::vector<QueryArgument> expectedResultSynonms;
	std::vector<QueryClause> expectedClauses;
	std::vector<QueryArgument> clauseArgs;
	std::vector<QueryArgument> patternArgs;
	std::unordered_set<std::string> relUsedSynonyms;
	std::unordered_set<std::string> patternUsedSynonyms;

	SECTION("1 synonym (pattern), no common syn") {
		std::string queryString = "assign that; Select that such that Parent*(124,135) pattern that(_,_\"cost\"_)";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("that"), EntityType::ASSIGN));

		//rel
		clauseArgs.push_back(QueryArgument(std::string("124"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("135"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("that");
		patternArgs.push_back(QueryArgument(std::string("_"), EntityType::WILD));
		patternArgs.push_back(QueryArgument(std::string("_cost_"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "that"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("2 synonym (1 rel, 1pattern), no common syn") {
		std::string queryString = "assign procedure, line2; Select procedure such that Parent*(line2,4) pattern procedure(\"jne\",\"jep\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("procedure"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("line2");
		clauseArgs.push_back(QueryArgument(std::string("line2"), EntityType::ASSIGN));
		clauseArgs.push_back(QueryArgument(std::string("4"), EntityType::INT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("procedure");
		patternArgs.push_back(QueryArgument(std::string("jne"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("jep"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "procedure"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (2rel, 1pattern), no common syn") {
		std::string queryString = "assign assign1; stmt s1, s2;  Select assign1 such that Parent*(s1,s2) pattern assign1(\"msg\",\"msg2\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("assign1"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("s1");
		relUsedSynonyms.insert("s2");

		clauseArgs.push_back(QueryArgument(std::string("s1"), EntityType::STMT));
		clauseArgs.push_back(QueryArgument(std::string("s2"), EntityType::STMT));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("assign1");

		patternArgs.push_back(QueryArgument(std::string("msg"), EntityType::STRING));
		patternArgs.push_back(QueryArgument(std::string("msg2"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "assign1"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("3 synonym (1rel, 2pattern), common assign syn") {
		std::string queryString = "assign ab12; variable x24; Select ab12 such that Parent*(13,ab12) pattern ab12(x24,\"test124\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("ab12"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("ab12");
		clauseArgs.push_back(QueryArgument(std::string("13"), EntityType::INT));
		clauseArgs.push_back(QueryArgument(std::string("ab12"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("ab12");
		patternUsedSynonyms.insert("x24");
		patternArgs.push_back(QueryArgument(std::string("x24"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("test124"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "ab12"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}

	SECTION("4 synonym, no common syn") {
		std::string queryString = "assign a123,a456; if ifs2; variable vr124; Select a456 such that Parent*(ifs2,a123) pattern a456(vr124,\"tele\")";
		PQLLexer tokeniser = PQLLexer(queryString);
		std::vector<PQLToken*> PQLTokens = tokeniser.tokenise();
		PQLParser parser = PQLParser(PQLTokens);
		Query actualQuery = parser.parse();

		expectedResultSynonms.push_back(QueryArgument(std::string("a456"), EntityType::ASSIGN));

		//rel
		relUsedSynonyms.insert("ifs2");
		relUsedSynonyms.insert("a123");
		clauseArgs.push_back(QueryArgument(std::string("ifs2"), EntityType::IF));
		clauseArgs.push_back(QueryArgument(std::string("a123"), EntityType::ASSIGN));
		expectedClauses.push_back(QueryClause(RelationRef::PARENT_T, clauseArgs, relUsedSynonyms));

		//pattern
		patternUsedSynonyms.insert("a456");
		patternUsedSynonyms.insert("vr124");
		patternArgs.push_back(QueryArgument(std::string("vr124"), EntityType::VAR));
		patternArgs.push_back(QueryArgument(std::string("tele"), EntityType::STRING));
		expectedClauses.push_back(QueryClause(RelationRef::PATTERN_A, patternArgs, patternUsedSynonyms, "a456"));

		std::vector<QueryArgument> actualResultSynonms = actualQuery.getResultSynonyms();
		std::vector<QueryClause> actualClauses = actualQuery.getClauses();
		bool isClausesEqual = std::equal(expectedClauses.begin(), expectedClauses.end(), actualClauses.begin());
		bool isResultSynonymEqual = std::equal(expectedResultSynonms.begin(), expectedResultSynonms.end(),
											   actualResultSynonms.begin());
		REQUIRE((isClausesEqual && isResultSynonymEqual));
	}
}