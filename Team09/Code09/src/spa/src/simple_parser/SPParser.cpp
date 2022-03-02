#include "SPParser.h"

SPParser::SPParser(std::vector<Token*> tokens) : tokens(std::move(tokens)), currentIdx(0), stmtNo(0) {}

Token* SPParser::peek() {
	return tokens[currentIdx];
}

Token* SPParser::get() {
	Token* currToken = peek();
	if (!isEndOfFile()) currentIdx++;
	return currToken;
}

bool SPParser::isEndOfFile() {
	return peek()->isEndOfFileToken();
}

bool SPParser::check(ParserTokenType t) {
	return peek()->getTokenType() == t;
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
	std::string val = peek()->getValue();
	return val == ")" || val == ";" || val == ">" || val == ">=" || val == "<" ||
		   val == "<=" || val == "==" || val == "!=";
}

void SPParser::clearExprStr() {
	exprStr = "";
}

int SPParser::getLeftBindingPower() {
	std::string op = peek()->getValue();
	if (op == "+" || op == "-") {
		return BindingPower::SUM;
	} else if (op == "*" || op == "/" || op == "%") {
		return BindingPower::PRODUCT;
	} else {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
}

BinaryOperator SPParser::getBinaryOperatorEnum() {
	if (!check(ParserTokenType::OPERATOR) ||
		strBinaryOpMap.find(peek()->getValue()) == strBinaryOpMap.end()) {
		throw std::runtime_error("Expected arithmetic operator but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string op = peek()->getValue();
	return strBinaryOpMap[op];
}

// factor: var_name
// 		 | const_value
// 		 | '(' expr ')'
ExprNode SPParser::parseOperand() {
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
	if (check("(")) {
		parenthesesStack++;
		get();
	} else {
		return true;
	}
	while (parenthesesStack != 0) {
		// is end of program or predicate but parentheses do not match
		if (isEndOfFile() || check("{"))
			throw std::runtime_error("Unmatched parentheses at line " + std::to_string(getStmtNo()));
		if (check("(")) parenthesesStack++;
		if (check(")")) parenthesesStack--;
		get();
	}
	bool rtv = !(check("&&") || check("||"));
	currentIdx = storeCurrIdx;
	return rtv;
}

ComparatorOperator SPParser::getComparatorOperatorEnum() {
	if (!check(ParserTokenType::OPERATOR) ||
		strComparatorOpMap.find(peek()->getValue()) == strComparatorOpMap.end()) {
		throw std::runtime_error("Expected comparator operator but got '" + peek()->getValue() + "' instead.\n");
	}
	std::string op = peek()->getValue();
	return strComparatorOpMap[op];
}

ConditionalOperator SPParser::getInfixConditionalOperatorEnum() {
	if (check("&&")) {
		return ConditionalOperator::AND;
	} else if (check("||")) {
		return ConditionalOperator::OR;
	} else {
		throw std::runtime_error("Expected '&&' or '||' but got '" + peek()->getValue() + "' instead.\n");
	}
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
	if (check("!")) {
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
	if (!check(ParserTokenType::INTEGER)) return nullptr;
	return std::make_shared<ConstantNode>(get()->getValue());
}

std::shared_ptr<VariableNode> SPParser::parseVariable() {
	if (!check(ParserTokenType::NAME)) return nullptr;
	return std::make_shared<VariableNode>(get()->getValue());
}

// procedure: 'procedure' proc_name '{' stmtLst '}'
std::shared_ptr<ProcedureNode> SPParser::parseProcedure() {
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
	if (check("}")) return nullptr;

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
	if (!check("=")) {
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

// Main function driving SPParser class (exposed API)
// program: procedure+
AST SPParser::parseProgram() {
	std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procedureMap;
  while (true) {
    if (check(ParserTokenType::END_OF_FILE)) {
      break;
    }
	  std::shared_ptr<ProcedureNode> procedureNode = parseProcedure();
    if (!procedureNode) {
      throw std::runtime_error("Expected 'procedure' but got '" + peek()->getValue() + "' instead.\n");
    }

    // SEMANTIC RULE: A program cannot have two procedures with the same name
    if ( procedureMap.find(procedureNode->getProcName()) != procedureMap.end() ) {
      throw std::runtime_error("There are 2 procedures with the same name '" + procedureNode->getProcName() + "'.\n");
    }

    procedureMap.insert(std::make_pair(procedureNode->getProcName(), procedureNode));
  }

  if (procedureMap.empty()) {
		throw std::runtime_error("There must be at least 1 procedure in a SIMPLE program!\n");
	}

	return std::make_shared<ProgramNode>(procedureMap);
}