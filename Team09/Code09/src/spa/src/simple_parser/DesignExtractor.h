#pragma once

#include "models/simple_parser/AST.h"
#include "models/simple_parser/AssignNode.h"
#include "models/simple_parser/CallNode.h"
#include "models/simple_parser/ExprNodes.h"
#include "models/simple_parser/IoNodes.h"
#include "models/simple_parser/IfNode.h"
#include "models/simple_parser/PredicateNodes.h"
#include "models/simple_parser/ProcedureNode.h"
#include "models/simple_parser/WhileNode.h"
#include "simple_parser/EntityStager.h"
#include "simple_parser/NestableRelationships.h"
#include "simple_parser/CFGExtractor.h"

#include <memory>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class DesignExtractor {
private:
	static inline std::unordered_map<std::string, NestableRelationships> procCache;
	AST ast;
	int totalStmt;

	std::stack<NestableRelationships> nestableRelationshipsStack;
	std::stack<std::shared_ptr<Node>> nodeStack;
	std::stack<std::shared_ptr<Node>> containerStack; //will contain ProcedureNode, IfNode, WhileNode, CallNode
	std::stack<std::string> callStack;

	void bubbleRelationshipInfo(NestableRelationships rs, std::unordered_set<int> unwantedChildren);

	void processStmtList(std::vector<std::shared_ptr<StmtNode>> stmtList);
	void processProcedure(std::shared_ptr<ProcedureNode> proc);
	void processPrintNode(std::shared_ptr<PrintNode> print);
	void processReadNode(std::shared_ptr<ReadNode> read);
	void processAssignNode(std::shared_ptr<AssignNode> assign);
	void processWhileNode(std::shared_ptr<WhileNode> whiles);
	void processIfNode(std::shared_ptr<IfNode> ifs);
	void processCallNode(std::shared_ptr<CallNode> call);
	void processStmt(std::shared_ptr<StmtNode> stmt);
	void processProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap);

public:
	DesignExtractor(AST ast, int stmtCount);
	static bool isCached(std::string procName);
	static NestableRelationships retrieve(std::string procName);
	static void cache(std::string procName, NestableRelationships rs);

	void extractDesignElements();
	void commit();
};
