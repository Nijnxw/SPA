#include <queue>
#include "OptimizerQuery.h"

std::vector<OptimizerGroup> OptimizerQuery::groupClauses() {
	std::unordered_set<std::string> visited;
	std::vector<OptimizerGroup> groups;

	for (const auto& keyVal: adjList) {
		if (!visited.count(keyVal.first)) {
			OptimizerGroup group = groupingHelper(keyVal.first, visited);
			auto adjList = group.getAdjList();
			if (!adjList.empty()) {
				groups.push_back(group);
			}
		}
	}

	return groups;
}

OptimizerGroup
OptimizerQuery::groupingHelper(const std::string& synonym, std::unordered_set<std::string>& visited) {
	visited.emplace(synonym);

	OptimizerGroup resultGroup;
	std::queue<std::string> queue;
	queue.push(synonym);

	while (!queue.empty()) {
		std::string currSyn = queue.front();
		queue.pop();
		for (const auto& clause: adjList.at(currSyn)) {
			resultGroup.addEdge(clause);
			if (!visited.count(clause.getTo())) {
				visited.emplace(clause.getTo());
				queue.push(clause.getTo());
			}
		}
	}

	return resultGroup;
}
