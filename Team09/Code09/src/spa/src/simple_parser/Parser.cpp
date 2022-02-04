#include <string>
#include <utility>
#include <vector>
#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) : tokens(std::move(tokens)), currentIdx(0), stmtNo(1) {}

Token* Parser::peek() {
	return tokens[currentIdx];
}

Token* Parser::get() {
	Token* currToken = peek();
	if (!isEndOfFile()) currentIdx++;
	return currToken;
}

bool Parser::isEndOfFile() {
	return peek()->isEndOfFileToken();
}

bool Parser::check(const std::string& s) {
	return peek()->getValue() == s;
}

bool Parser::check(TokenType t) {
	return peek()->getTokenType() == t;
}

bool Parser::expect(const std::string& s) {
	if (!check(s)) {
		throw std::runtime_error("Expected '" + s + "' but got '" + peek()->getValue() + "' instead.\n");
	}
	get();
	return true;
}

std::shared_ptr<VariableNode> Parser::parseVariable() {
	if (!check(TokenType::NAME)) {
		throw std::runtime_error("Invalid variable name!\n");
	}
	return std::make_shared<VariableNode>(get()->getValue());
}

// procedure: 'procedure' proc_name '{' stmtLst '}'
std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
	expect("procedure");
	if (!check(TokenType::NAME)) {
		throw std::runtime_error("Expected a valid procedure name but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string procName = get()->getValue();
	expect("{");
	std::vector<std::shared_ptr<StmtNode>> stmtLst = parseStmtLst();
	expect("}");
	return std::make_shared<ProcedureNode>(stmtLst, procName);
}

// stmtLst: stmt+
std::vector<std::shared_ptr<StmtNode>> Parser::parseStmtLst() {
	std::vector<std::shared_ptr<StmtNode>> stmtLst;
	while (true) {
		std::shared_ptr<StmtNode> stmt = parseStatement();
		stmtNo++;
		if (!stmt) break;
		stmtLst.push_back(stmt);
	}
	if (stmtLst.empty()) {
		throw std::runtime_error("There must be at least 1 statement in a statement list!\n");
	}
	return stmtLst;
}

std::shared_ptr<StmtNode> Parser::parseStatement() {
	if (check("}")) return nullptr;
	int currIdx = currentIdx;
	std::shared_ptr<ReadNode> readNode = parseRead();
	if (readNode) return readNode;
	currentIdx = currIdx;
	return nullptr;
}

// read: 'read' var_name';'
std::shared_ptr<ReadNode> Parser::parseRead() {
	expect("read");
	std::shared_ptr<VariableNode> variableNode = parseVariable();
	expect(";");
	return std::make_shared<ReadNode>(stmtNo, variableNode);
}

// Main function driving Parser class (exposed API)
// program: procedure
AST Parser::parseProgram() {
	std::vector<std::shared_ptr<ProcedureNode>> procedureList;
	std::shared_ptr<ProcedureNode> procedureNode = parseProcedure();
	if (!procedureNode) {
		throw std::runtime_error("There must be at least 1 procedure in a SIMPLE program!\n");
	}
	procedureList.push_back(procedureNode);
	return std::make_shared<ProgramNode>(procedureList);
}