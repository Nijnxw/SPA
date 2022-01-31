#include <unordered_set>

namespace PKBUtil
{
    template <typename T>
    std::unordered_set<T> unorderedSetIntersection(const std::unordered_set<T>& set1, const std::unordered_set<T>& set2)
    {
        std::unordered_set<T> resultSet;
        if (set1.size() < set2.size()) {
            for (const auto& ele : set1) {
                if (set2.find(ele) != set2.end())
                    resultSet.insert(ele);
            }
        }
        else {
            for (const auto& ele : set2) {
                if (set1.find(ele) != set1.end())
                    resultSet.insert(ele);
            }
        }
        return resultSet;
    }
}
