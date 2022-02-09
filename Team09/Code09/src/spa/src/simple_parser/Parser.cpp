#include <string>
#include <utility>
#include <vector>
#include "Parser.h"
#include "util/RPN.h"

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

bool Parser::check(ParserTokenType t) {
	return peek()->getTokenType() == t;
}

bool Parser::check(const std::string& s) {
	return peek()->getValue() == s;
}

bool Parser::expect(const std::string& s) {
	if (!check(s)) {
		throw std::runtime_error("Expected '" + s + "' but got '" + peek()->getValue() + "' instead.\n");
	}
	get();
	return true;
}

int Parser::getLeftBindingPower() {
	std::string op = peek()->getValue();
	if (op == "+" || op == "-") {
		return 10;
	} else if (op == "*" || op == "/" || op == "%") {
		return 20;
	} else {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
}

BinaryOperator Parser::getOperatorEnum() {
	if (!check(ParserTokenType::OPERATOR)) {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string op = peek()->getValue();
	if (op == "+") {
		return BinaryOperator::PLUS;
	} else if (op == "-") {
		return BinaryOperator::MINUS;
	} else if (op == "*") {
		return BinaryOperator::TIMES;
	} else if (op == "/") {
		return BinaryOperator::DIVIDE;
	} else if (op == "%") {
		return BinaryOperator::MODULO;
	} else {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
}

// factor: var_name
// 		 | const_value
// 		 | '(' expr ')'
ExprNode Parser::parseOperand() {
	if (check(ParserTokenType::NAME)) {
		exprStr += peek()->getValue();
		return parseVariable();
	} else if (check(ParserTokenType::INTEGER)) {
		exprStr += peek()->getValue();
		return parseConstant();
	} else if (check("(")) {
		exprStr += get()->getValue();
		ExprNode expr = parseExpr();
		expect(")");
		exprStr += ")";
		return expr;
	} else {
		throw std::runtime_error("Expected an expression but got '" + peek()->getValue() + "' instead.\n");
	}
}

ExprNode Parser::parseOperator(const ExprNode& lhs) {
	ExprNode rhs;
	BinaryOperator op = getOperatorEnum();
	exprStr += get()->getValue();
	switch (op) {
		case BinaryOperator::PLUS:
		case BinaryOperator::MINUS:
			rhs = parseExpression(10);
			return std::make_shared<BinaryOperatorNode>(op, lhs, rhs);
		case BinaryOperator::TIMES:
		case BinaryOperator::DIVIDE:
		case BinaryOperator::MODULO:
			rhs = parseExpression(20);
			return std::make_shared<BinaryOperatorNode>(op, lhs, rhs);
		default:
			throw std::runtime_error("Expected arithmetic operator but got invalid operator instead.\n");
	}
}

ExprNode Parser::parseExpression(int rightBindingPower = 0) {
	ExprNode left = parseOperand();
	while (!check(";") && !check(")") && rightBindingPower < getLeftBindingPower()) {
		left = parseOperator( left);
	}
	return left;
}

// expr: expr '+' term
// 	   | expr '-' term
// 	   | term
// term: term '*' factor
// 	   | term '/' factor
// 	   | term '%' factor
// 	   | factor
ExprNode Parser::parseExpr() {
	return parseExpression(0);
}

std::shared_ptr<ConstantNode> Parser::parseConstant() {
	if (!check(ParserTokenType::INTEGER)) return nullptr;
	return std::make_shared<ConstantNode>(get()->getValue());
}

std::shared_ptr<VariableNode> Parser::parseVariable() {
	if (!check(ParserTokenType::NAME)) return nullptr;
	return std::make_shared<VariableNode>(get()->getValue());
}

// procedure: 'procedure' proc_name '{' stmtLst '}'
std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
	if (!check("procedure")) return nullptr;
	expect("procedure");
	if (!check(ParserTokenType::NAME)) {
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

	std::shared_ptr<ReadNode> readNode = parseRead();
	if (readNode) return readNode;

	std::shared_ptr<PrintNode> printNode = parsePrint();
	if (printNode) return printNode;

	std::shared_ptr<AssignNode> assignNode = parseAssign();
	if (assignNode) return assignNode;

	throw std::runtime_error("Invalid statement syntax at statement " + std::to_string(stmtNo) + ".\n");
}

// read: 'read' var_name';'
std::shared_ptr<ReadNode> Parser::parseRead() {
	if (!check("read")) return nullptr;
	expect("read");
	std::shared_ptr<VariableNode> variableNode = parseVariable();
	if (!variableNode) {
		throw std::runtime_error("Expected a variable name but got '" + peek()->getValue() + "' instead.\n");
	}
	expect(";");
	return std::make_shared<ReadNode>(stmtNo, variableNode);
}

// print: 'print' var_name';'
std::shared_ptr<PrintNode> Parser::parsePrint() {
	if (!check("print")) return nullptr;
	expect("print");
	std::shared_ptr<VariableNode> variableNode = parseVariable();
	if (!variableNode) {
		throw std::runtime_error("Expected a variable name but got '" + peek()->getValue() + "' instead.\n");
	}
	expect(";");
	return std::make_shared<PrintNode>(stmtNo, variableNode);
}

// assign: var_name '=' expr ';'
std::shared_ptr<AssignNode> Parser::parseAssign() {
	std::shared_ptr<VariableNode> varNode = parseVariable();
	if (!varNode) return nullptr;
	expect("=");
	ExprNode exprNode = parseExpr();
	expect(";");
	std::string postfix = RPN::convertToRpn(exprStr);
	exprStr = "";
	return std::make_shared<AssignNode>(stmtNo, varNode, exprNode, postfix);
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