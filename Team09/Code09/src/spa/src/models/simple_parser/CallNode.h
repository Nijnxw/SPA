#include "StmtNode.h"
#include "NodeType.h"

#include <string>

class CallNode : public StmtNode {
private:
	std::string procedure;

public:
	CallNode(int sn, std::string s);
	std::string getProcedureName() const;
	bool operator==(const Node& other) const override;
};