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
	std::queue<std::string> synQueue;
	synQueue.push(synonym);

	while (!synQueue.empty()) {
		std::string currSyn = synQueue.front();
		synQueue.pop();
		for (const auto& clause: adjList.at(currSyn)) {
			resultGroup.addEdge(clause);
			if (!visited.count(clause.getTo())) {
				visited.emplace(clause.getTo());
				synQueue.push(clause.getTo());
			}
		}
	}

	return resultGroup;
}
