#pragma once

#include "PredicateNodes.h"
#include "StmtNode.h"

#include <memory>
#include <vector>

class WhileNode : public StmtNode {
private:
	std::shared_ptr<PredicateNode> predicate;
	std::vector<std::shared_ptr<StmtNode>> stmtList;

public:
	WhileNode(int sn, std::shared_ptr<PredicateNode> pred, std::shared_ptr<std::shared_ptr<StmtNode>> then, std::shared_ptr<std::shared_ptr<StmtNode>> els);
	std::shared_ptr<PredicateNode> getPredicate();
	std::vector<std::shared_ptr<StmtNode>> getStmtList();
	bool operator==(const Node& other) const override;
};