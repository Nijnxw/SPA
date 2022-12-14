#include "SPParser.h"

SPParser::SPParser(std::vector<SPToken*> tokens) : tokens(std::move(tokens)), currentIdx(0), stmtNo(0),
																									 callStmtValidator(CallStmtValidator()) {}

SPToken* SPParser::peek() {
	return tokens[currentIdx];
}

SPToken* SPParser::get() {
	SPToken* currToken = peek();
	if (!isEndOfFile()) currentIdx++;
	return currToken;
}

bool SPParser::isEndOfFile() {
	return peek()->getType() == TokenType::END_OF_FILE;
}

bool SPParser::check(TokenType t) {
	return peek()->getType() == t;
}

bool SPParser::check(const std::string& s) {
	return peek()->getValue() == s;
}

bool SPParser::expect(const std::string& s) {
	if (!check(s)) {
		throw std::runtime_error("Expected '" + s + "' but got '" + peek()->getValue() + "' instead.\n");
	}
	get();
	return true;
}

int SPParser::getStmtNo() {
	stmtNo++;
	return stmtNo;
}

bool SPParser::isEndOfExpr() {
	TokenType type = peek()->getType();
	return type == TokenType::CLOSE_PARAN || type == TokenType::SEMICOLON
			|| type == TokenType::MORE_THAN || type == TokenType::MORE_THAN_EQUALS
			|| type == TokenType::LESS_THAN || type == TokenType::LESS_THAN_EQUALS
			|| type == TokenType::EQUAL || type == TokenType::NOT_EQUAL;
}

void SPParser::clearExprStr() {
	exprStr = "";
}

int SPParser::getLeftBindingPower() {
	TokenType opType = peek()->getType();
	if (opType == TokenType::PLUS || opType == TokenType::MINUS) {
		return BindingPower::SUM;
	} else if (opType == TokenType::TIMES || opType == TokenType::DIVIDE || opType == TokenType::MODULO) {
		return BindingPower::PRODUCT;
	} else {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
}

BinaryOperator SPParser::getBinaryOperatorEnum() {
	// the next token is a binary operator
	assert (strBinaryOpMap.find(peek()->getType()) != strBinaryOpMap.end());
	TokenType op = peek()->getType();
	return strBinaryOpMap[op];
}

// factor: var_name
// 		 | const_value
// 		 | '(' expr ')'
ExprNode SPParser::parseOperand() {
	if (check(TokenType::NAME)) {
		exprStr += peek()->getValue();
		return parseVariable();
	} else if (check(TokenType::INTEGER)) {
		exprStr += peek()->getValue();
		return parseConstant();
	} else if (check(TokenType::OPEN_PARAN)) {
		exprStr += get()->getValue();
		ExprNode expr = parseExpr();
		expect(")");
		exprStr += ")";
		return expr;
	} else {
		throw std::runtime_error("Expected an expression but got '" + peek()->getValue() + "' instead.\n");
	}
}

ExprNode SPParser::parseOperator(const ExprNode& lhs) {
	ExprNode rhs;
	BinaryOperator op = getBinaryOperatorEnum();
	exprStr += get()->getValue();
	switch (op) {
		case BinaryOperator::PLUS:
		case BinaryOperator::MINUS:
			rhs = parseExpression(BindingPower::SUM);
			return std::make_shared<BinaryOperatorNode>(op, lhs, rhs);
		case BinaryOperator::TIMES:
		case BinaryOperator::DIVIDE:
		case BinaryOperator::MODULO:
			rhs = parseExpression(BindingPower::PRODUCT);
			return std::make_shared<BinaryOperatorNode>(op, lhs, rhs);
		default:
			throw std::runtime_error("Expected arithmetic operator but got invalid operator instead.\n");
	}
}

ExprNode SPParser::parseExpression(int rightBindingPower = BindingPower::OPERAND) {
	ExprNode left = parseOperand();
	while (!isEndOfExpr() && rightBindingPower < getLeftBindingPower()) {
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
ExprNode SPParser::parseExpr() {
	return parseExpression(BindingPower::OPERAND);
}

bool SPParser::isTerminalPredicate() {
	// check if future token do not have '&&' or '||' tokens
	int storeCurrIdx = currentIdx;
	int parenthesesStack = 0;
	if (check(TokenType::OPEN_PARAN)) {
		parenthesesStack++;
		get();
	} else {
		return true;
	}
	while (parenthesesStack != 0) {
		// is end of program or predicate but parentheses do not match
		if (isEndOfFile() || check(TokenType::OPEN_CURLY)) {
			throw std::runtime_error("Unmatched parentheses at line " + std::to_string(getStmtNo()));
		}
		if (check(TokenType::OPEN_PARAN)) parenthesesStack++;
		if (check(TokenType::CLOSE_PARAN)) parenthesesStack--;
		get();
	}
	bool rtv = !(check(TokenType::AND) || check(TokenType::OR));
	currentIdx = storeCurrIdx;
	return rtv;
}

ComparatorOperator SPParser::getComparatorOperatorEnum() {
	if (strComparatorOpMap.find(peek()->getType()) == strComparatorOpMap.end()) {
		throw std::runtime_error("Expected comparator operator but got '" + peek()->getValue() + "' instead.\n");
	}
	TokenType op = peek()->getType();
	return strComparatorOpMap[op];
}

ConditionalOperator SPParser::getInfixConditionalOperatorEnum() {
	assert (check(TokenType::AND) || check(TokenType::OR));
	if (check(TokenType::AND)) {
		return ConditionalOperator::AND;
	}
	return ConditionalOperator::OR;
}

// rel_factor: var_name | const_value | expr
// rel_expr: rel_factor '>' rel_factor
//		   | rel_factor '>=' rel_factor
//		   | rel_factor '<' rel_factor
//		   | rel_factor '<=' rel_factor
//		   | rel_factor '==' rel_factor
//		   | rel_factor '!=' rel_factor
std::shared_ptr<RelExprNode> SPParser::parseRelExpr() {
	ExprNode lhs = parseExpr();
	clearExprStr();
	ComparatorOperator op = getComparatorOperatorEnum();
	get(); // advance to the next token
	ExprNode rhs = parseExpr();
	clearExprStr();
	return std::make_shared<RelExprNode>(lhs, op, rhs);
}

// cond_expr: rel_expr
//			| '!' '(' cond_expr ')'
//			| '(' cond_expr ')' '&&' '(' cond_expr ')'
//			| '(' cond_expr ')' '||' '(' cond_expr ')'
std::shared_ptr<PredicateNode> SPParser::parsePredicate() {
	if (check(TokenType::NOT)) {
		expect("!");
		expect("(");
		std::shared_ptr<PredicateNode> predicateNode = parsePredicate();
		expect(")");
		return std::make_shared<PredicateNode>(ConditionalOperator::NOT, predicateNode);
	} else if (!isTerminalPredicate()) {
		expect("(");
		std::shared_ptr<PredicateNode> lhs = parsePredicate();
		expect(")");
		ConditionalOperator op = getInfixConditionalOperatorEnum();
		get(); // advance to next
		expect("(");
		std::shared_ptr<PredicateNode> rhs = parsePredicate();
		expect(")");
		return std::make_shared<PredicateNode>(lhs, op, rhs);
	} else {
		return std::make_shared<PredicateNode>(parseRelExpr());
	}
}

std::shared_ptr<ConstantNode> SPParser::parseConstant() {
	if (!check(TokenType::INTEGER)) return nullptr;
	return std::make_shared<ConstantNode>(get()->getValue());
}

std::shared_ptr<VariableNode> SPParser::parseVariable() {
	if (!check(TokenType::NAME)) return nullptr;
	return std::make_shared<VariableNode>(get()->getValue());
}

// procedure: 'procedure' proc_name '{' stmtLst '}'
std::shared_ptr<ProcedureNode> SPParser::parseProcedure() {
	if (!check("procedure")) return nullptr;
	expect("procedure");
	if (!check(TokenType::NAME)) {
		throw std::runtime_error("Expected a valid procedure name but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string procName = get()->getValue();

	// SEMANTIC RULE: A program cannot have two procedures with the same name
	if (callStmtValidator.programHasProcName(procName)) {
		throw std::runtime_error("There are 2 procedures with the same name '" + procName + "'.\n");
	}
	currProcName = procName;
	callStmtValidator.addProcName(procName);

	expect("{");
	std::vector<std::shared_ptr<StmtNode>> stmtLst = parseStmtLst();
	expect("}");
	return std::make_shared<ProcedureNode>(stmtLst, procName);
}

// stmtLst: stmt+
std::vector<std::shared_ptr<StmtNode>> SPParser::parseStmtLst() {
	std::vector<std::shared_ptr<StmtNode>> stmtLst;
	while (true) {
		std::shared_ptr<StmtNode> stmt = parseStatement();
		if (!stmt) break;
		stmtLst.push_back(stmt);
	}
	if (stmtLst.empty()) {
		throw std::runtime_error("There must be at least 1 statement in a statement list!\n");
	}
	return stmtLst;
}

std::shared_ptr<StmtNode> SPParser::parseStatement() {
	if (check(TokenType::CLOSE_CURLY)) return nullptr;

	std::shared_ptr<AssignNode> assignNode = parseAssign();
	if (assignNode) return assignNode;

	std::shared_ptr<ReadNode> readNode = parseRead();
	if (readNode) return readNode;

	std::shared_ptr<PrintNode> printNode = parsePrint();
	if (printNode) return printNode;

	std::shared_ptr<WhileNode> whileNode = parseWhile();
	if (whileNode) return whileNode;

	std::shared_ptr<IfNode> ifNode = parseIf();
	if (ifNode) return ifNode;

	std::shared_ptr<CallNode> callNode = parseCall();
	if (callNode) return callNode;

	throw std::runtime_error("Invalid statement syntax at statement " + std::to_string(getStmtNo()) + ".\n");
}

// read: 'read' var_name';'
std::shared_ptr<ReadNode> SPParser::parseRead() {
	if (!check("read")) return nullptr;
	expect("read");
	std::shared_ptr<VariableNode> variableNode = parseVariable();
	if (!variableNode) {
		throw std::runtime_error("Expected a variable name but got '" + peek()->getValue() + "' instead.\n");
	}
	expect(";");
	return std::make_shared<ReadNode>(getStmtNo(), variableNode);
}

// print: 'print' var_name';'
std::shared_ptr<PrintNode> SPParser::parsePrint() {
	if (!check("print")) return nullptr;
	expect("print");
	std::shared_ptr<VariableNode> variableNode = parseVariable();
	if (!variableNode) {
		throw std::runtime_error("Expected a variable name but got '" + peek()->getValue() + "' instead.\n");
	}
	expect(";");
	return std::make_shared<PrintNode>(getStmtNo(), variableNode);
}

// assign: var_name '=' expr ';'
std::shared_ptr<AssignNode> SPParser::parseAssign() {
	int storedCurrIdx = currentIdx;
	std::shared_ptr<VariableNode> varNode = parseVariable();
	if (!varNode) return nullptr;
	if (!check(TokenType::ASSIGNMENT_EQUAL)) {
		// var_name could be a keyword (read, print, if, while)
		// if next token is not '-', restore token pointer and return nullptr
		// for parseStmt to parse other types of stmts
		currentIdx = storedCurrIdx;
		return nullptr;
	}
	expect("=");
	ExprNode exprNode = parseExpr();
	expect(";");
	std::string postfix = RPN::convertToRpn(exprStr);
	clearExprStr();
	return std::make_shared<AssignNode>(getStmtNo(), varNode, exprNode, postfix);
}

// while: 'while' '(' cond_expr ')' '{' stmtLst '}'
std::shared_ptr<WhileNode> SPParser::parseWhile() {
	if (!check("while")) return nullptr;
	int currStmtNo = getStmtNo();
	expect("while");
	expect("(");
	std::shared_ptr<PredicateNode> predicateNode = parsePredicate();
	expect(")");
	expect("{");
	std::vector<std::shared_ptr<StmtNode>> stmtLst = parseStmtLst();
	expect("}");
	return std::make_shared<WhileNode>(currStmtNo, predicateNode, stmtLst);
}

// if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
std::shared_ptr<IfNode> SPParser::parseIf() {
	if (!check("if")) return nullptr;
	int currStmtNo = getStmtNo();
	expect("if");
	expect("(");
	std::shared_ptr<PredicateNode> predicateNode = parsePredicate();
	expect(")");
	expect("then");
	expect("{");
	std::vector<std::shared_ptr<StmtNode>> thenStmtLst = parseStmtLst();
	expect("}");
	expect("else");
	expect("{");
	std::vector<std::shared_ptr<StmtNode>> elseStmtLst = parseStmtLst();
	expect("}");
	return std::make_shared<IfNode>(currStmtNo, predicateNode, thenStmtLst, elseStmtLst);
}

// call: 'call' proc_name';'
std::shared_ptr<CallNode> SPParser::parseCall() {
	if (!check("call")) return nullptr;
	expect("call");
	if (!check(TokenType::NAME)) {
		throw std::runtime_error("Expected a valid procedure name but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string calleeProcName = get()->getValue();

	assert(!currProcName.empty());
	callStmtValidator.addProcCall(currProcName, calleeProcName);

	expect(";");
	return std::make_shared<CallNode>(getStmtNo(), calleeProcName);
}

// Main function driving SPParser class (exposed API)
// program: procedure+
AST SPParser::parseProgram() {
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procedureMap;
	while (true) {
		if (isEndOfFile()) {
			break;
		}

		std::shared_ptr<ProcedureNode> procedureNode = parseProcedure();
		if (!procedureNode) {
			throw std::runtime_error("Expected 'procedure' but got '" + peek()->getValue() + "' instead.\n");
		}

		procedureMap.insert(std::make_pair(procedureNode->getProcName(), procedureNode));
	}

	if (procedureMap.empty()) {
		throw std::runtime_error("There must be at least 1 procedure in a SIMPLE program!\n");
	}

	// check if all call semantic rules are held, else throws error
	callStmtValidator.checkCallStmtsValidity();

	return std::make_shared<ProgramNode>(procedureMap);
}

int SPParser::getStmtCount() const {
	return stmtNo;
}