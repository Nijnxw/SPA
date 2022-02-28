#include "Node.h"
#include "NodeType.h"

#include <string>

class CallNode : public Node {
private:
	std::string procedure;

public:
	CallNode(std::string s);
	std::string getProcedureName() const;
	bool operator==(const Node& other) const override;
};