#pragma once

#include "simple_parser/Token.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/AssignNode.h"

#include <vector>
#include <stdexcept>

class Parser {
private:
	int currentIdx = 0;
	int stmtNo = 1;
	std::vector<Token*> tokens;
	std::string exprStr;

	Token* peek();
	Token* get();

	bool isEndOfFile();
	bool check(ParserTokenType t);
	bool check(const std::string& s);
	bool expect(const std::string& s);

	int getLeftBindingPower();
	BinaryOperator getOperatorEnum();
	ExprNode parseOperand();
	ExprNode parseOperator(const ExprNode& lhs);
	ExprNode parseExpression(int rightBindingPower);
	ExprNode parseExpr();

	std::shared_ptr<ConstantNode> parseConstant();
	std::shared_ptr<VariableNode> parseVariable();
	std::shared_ptr<ProcedureNode> parseProcedure();

	std::vector<std::shared_ptr<StmtNode>> parseStmtLst();
	std::shared_ptr<StmtNode> parseStatement();
	std::shared_ptr<ReadNode> parseRead();
	std::shared_ptr<PrintNode> parsePrint();
	std::shared_ptr<AssignNode> parseAssign();

public:
	explicit Parser(std::vector<Token*> tokens);

	AST parseProgram();
};