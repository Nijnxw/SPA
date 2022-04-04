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
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class DesignExtractor {
private:
	static inline std::unordered_map<std::string, NestableRelationships> procCache;
	AST ast;
	int totalStmt;
	NestableRelationships processStmtList(std::vector<std::string> callStack, std::vector<std::shared_ptr<StmtNode>> stmtList);
	NestableRelationships processProcedure(std::vector<std::string> callStack, std::shared_ptr<ProcedureNode> proc);
	NestableRelationships processPrintNode(std::shared_ptr<PrintNode> print);
	NestableRelationships processReadNode(std::shared_ptr<ReadNode> read);
	NestableRelationships processAssignNode(std::shared_ptr<AssignNode> assign);
	NestableRelationships processWhileNode(std::vector<std::string> callStack, std::shared_ptr<WhileNode> whiles);
	NestableRelationships processIfNode(std::vector<std::string> callStack, std::shared_ptr<IfNode> ifs);
	NestableRelationships processCallNode(std::vector<std::string> callStack, std::shared_ptr<CallNode> call);
	NestableRelationships processStmt(std::vector<std::string> callStack, std::shared_ptr<StmtNode> stmt);
	void processProcedureList(std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> procMap);

public:
	DesignExtractor(AST ast, int stmtCount);
	static bool isCached(std::string procName);
	static NestableRelationships retrieve(std::string procName);
	static void cache(std::string procName, NestableRelationships rs);

	void extractDesignElements();
	void commit();
};
