#pragma once

#include "PredicateNodes.h"
#include "NodeType.h"
#include "StmtNode.h"

#include <memory>
#include <vector>

class IfNode : public StmtNode {
private:
	std::shared_ptr<PredicateNode> predicate;
	std::vector<std::shared_ptr<StmtNode>> thenStmtList;
	std::vector<std::shared_ptr<StmtNode>> elseStmtList;

public:
	IfNode(int sn, std::shared_ptr<PredicateNode> pred, std::vector<std::shared_ptr<StmtNode>> then, std::vector<std::shared_ptr<StmtNode>> els);
	std::shared_ptr<PredicateNode> getPredicate() const;
	std::vector<std::shared_ptr<StmtNode>> getThenStmtList() const;
	std::vector<std::shared_ptr<StmtNode>> getElseStmtList() const;
	bool operator==(const Node& other) const override;
};