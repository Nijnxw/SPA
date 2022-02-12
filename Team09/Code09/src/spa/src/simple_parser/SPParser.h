#pragma once

#include "simple_parser/Token.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/WhileNode.h"

#include <vector>
#include <stdexcept>
#include <unordered_map>

class SPParser {
private:
	int currentIdx = 0;
	int stmtNo = 1;
	std::vector<Token*> tokens;
	std::string exprStr;

	std::unordered_map<std::string, BinaryOperator> strBinaryOpMap = {
		{"+", BinaryOperator::PLUS},
		{"-", BinaryOperator::MINUS},
		{"*", BinaryOperator::TIMES},
		{"/", BinaryOperator::DIVIDE},
		{"%", BinaryOperator::MODULO},
	};

	std::unordered_map<std::string, ComparatorOperator> strComparatorOpMap = {
		{">", ComparatorOperator::GT},
		{">=", ComparatorOperator::GTE},
		{"<", ComparatorOperator::LT},
		{"<=", ComparatorOperator::LTE},
		{"==", ComparatorOperator::EQ},
		{"!=", ComparatorOperator::NEQ},
	};

	Token* peek();
	Token* get();

	bool isEndOfFile();
	bool check(ParserTokenType t);
	bool check(const std::string& s);
	bool expect(const std::string& s);

	enum BindingPower {
		OPERAND = 0,
		SUM = 10,
		PRODUCT = 20,
	};

	bool isEndOfExpr();
	int getLeftBindingPower();
	BinaryOperator getBinaryOperatorEnum();
	ExprNode parseOperand();
	ExprNode parseOperator(const ExprNode& lhs);
	ExprNode parseExpression(int rightBindingPower);
	ExprNode parseExpr();

	ComparatorOperator getComparatorOperatorEnum();
	ConditionalOperator getPrefixConditionalOperatorEnum();
	ConditionalOperator getInfixConditionalOperatorEnum();
	std::shared_ptr<RelExprNode> parseRelExpr();
	std::shared_ptr<PredicateNode> parsePredicate();

	std::shared_ptr<ConstantNode> parseConstant();
	std::shared_ptr<VariableNode> parseVariable();
	std::shared_ptr<ProcedureNode> parseProcedure();

	std::vector<std::shared_ptr<StmtNode>> parseStmtLst();
	std::shared_ptr<StmtNode> parseStatement();
	std::shared_ptr<ReadNode> parseRead();
	std::shared_ptr<PrintNode> parsePrint();
	std::shared_ptr<AssignNode> parseAssign();
	std::shared_ptr<WhileNode> parseWhile();

public:
	explicit SPParser(std::vector<Token*> tokens);

	AST parseProgram();
};