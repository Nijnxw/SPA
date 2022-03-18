#pragma once

#include "simple_parser/SPToken.h"
#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/CallNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/WhileNode.h"
#include "util/RPN.h"
#include "CallStmtValidator.h"

#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>

class SPParser {
private:
	int currentIdx = 0;
	int stmtNo = 0;
	std::vector<SPToken*> tokens;
	std::string exprStr;
	std::string currProcName;
	CallStmtValidator callStmtValidator;

	std::unordered_map<TokenType, BinaryOperator> strBinaryOpMap = {
		{TokenType::PLUS, BinaryOperator::PLUS},
		{TokenType::MINUS, BinaryOperator::MINUS},
		{TokenType::TIMES, BinaryOperator::TIMES},
		{TokenType::DIVIDE, BinaryOperator::DIVIDE},
		{TokenType::MODULO, BinaryOperator::MODULO},
	};

	std::unordered_map<TokenType, ComparatorOperator> strComparatorOpMap = {
		{TokenType::MORE_THAN, ComparatorOperator::GT},
		{TokenType::MORE_THAN_EQUALS, ComparatorOperator::GTE},
		{TokenType::LESS_THAN, ComparatorOperator::LT},
		{TokenType::LESS_THAN_EQUALS, ComparatorOperator::LTE},
		{TokenType::EQUAL, ComparatorOperator::EQ},
		{TokenType::NOT_EQUAL, ComparatorOperator::NEQ},
	};

	SPToken* peek();
	SPToken* get();

	bool isEndOfFile();
	bool check(TokenType t);
	bool check(const std::string& s);
	bool expect(const std::string& s);

	int getStmtNo();

	enum BindingPower {
		OPERAND = 0,
		SUM = 10,
		PRODUCT = 20,
	};

	bool isEndOfExpr();
	void clearExprStr();
	int getLeftBindingPower();
	BinaryOperator getBinaryOperatorEnum();
	ExprNode parseOperand();
	ExprNode parseOperator(const ExprNode& lhs);
	ExprNode parseExpression(int rightBindingPower);
	ExprNode parseExpr();

	bool isTerminalPredicate();
	ComparatorOperator getComparatorOperatorEnum();
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
	std::shared_ptr<IfNode> parseIf();
	std::shared_ptr<CallNode> parseCall();

public:
	explicit SPParser(std::vector<SPToken*> tokens);

	AST parseProgram();
	int getStmtCount() const;
};