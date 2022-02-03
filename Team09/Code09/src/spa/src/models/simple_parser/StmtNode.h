#pragma once

#include "NodeType.h"
#include "Node.h"

#include <vector>

class StmtNode : public Node {
private:
	int stmtNo;

protected:
	StmtNode(NodeType t, int sn);

public:
	int getStmtNumber();
};