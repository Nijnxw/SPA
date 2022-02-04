#pragma once

#include "simple_parser/Token.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"

#include <vector>
#include <stdexcept>

class Parser {
private:
	int currentIdx = 0;
	int stmtNo = 1;
	std::vector<Token*> tokens;

	Token* peek();
	Token* get();

	bool isEndOfFile();
	bool check(const std::string& s);
	bool check(TokenType t);
	bool expect(const std::string& s);

	std::shared_ptr<VariableNode> parseVariable();
	std::shared_ptr<ProcedureNode> parseProcedure();

	std::vector<std::shared_ptr<StmtNode>> parseStmtLst();
	std::shared_ptr<StmtNode> parseStatement();
	std::shared_ptr<ReadNode> parseRead();

public:
	explicit Parser(std::vector<Token*> tokens);

	AST parseProgram();
};