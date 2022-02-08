#pragma once

#include "PredicateNodes.h"
#include "StmtNode.h"

#include <memory>
#include <vector>

class IfNode : public StmtNode {
private:
	std::shared_ptr<PredicateNode> predicate;
	std::vector<std::shared_ptr<StmtNode>> thenStmtList;
	std::vector<std::shared_ptr<StmtNode>> elseStmtList;

public:
	IfNode(int sn, std::shared_ptr<PredicateNode> pred, std::shared_ptr<std::shared_ptr<StmtNode>> then, std::shared_ptr<std::shared_ptr<StmtNode>> else);
	std::shared_ptr<PredicateNode> getPredicate();
	std::vector<std::shared_ptr<StmtNode>> getThenStmtList();
	std::vector<std::shared_ptr<StmtNode>> getElseStmtList();
	bool operator==(const Node& other) const override;
};