#pragma once

#include "PredicateNodes.h"
#include "NodeType.h"
#include "StmtNode.h"

#include <memory>
#include <vector>

class WhileNode : public StmtNode {
private:
	std::shared_ptr<PredicateNode> predicate;
	std::vector<std::shared_ptr<StmtNode>> stmtList;

public:
	WhileNode(int sn, std::shared_ptr<PredicateNode> pred, std::vector<std::shared_ptr<StmtNode>> stmts);
	std::shared_ptr<PredicateNode> getPredicate() const;
	std::vector<std::shared_ptr<StmtNode>> getStmtList() const;
	bool operator==(const Node& other) const override;
};