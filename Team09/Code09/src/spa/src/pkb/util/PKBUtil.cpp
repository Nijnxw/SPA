#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace PKBUtil {
    struct hashFunction {
        template <class T1, class T2>
        size_t operator()(const std::pair<T1, T2>& p) const
        {
            auto hash1 = std::hash<T1>{}(p.first);
            auto hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    template <typename T>
    static std::unordered_set<T> unorderedSetIntersection(const std::unordered_set<T>& set1, const std::unordered_set<T>& set2) {
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

    static bool addToMapWithSet(std::unordered_map<int, std::unordered_set<int>>& map, const int key, const int value) {
        bool isAdded = true;

        if (map.count(key) <= 0) {
            std::unordered_set<int> newSet;
            isAdded = isAdded && newSet.insert(value).second;
            isAdded = isAdded && map.insert({ key, newSet }).second;
        }
        else {
            std::unordered_set<int>& set = map[key];
            isAdded = isAdded && set.insert(value).second;
        }

        return isAdded;
    }

    static bool addToMapWithVector(std::unordered_map<int, std::vector<int>>& map, const int key, const int value) {
        bool isAdded = true;

        if (map.count(key) <= 0) {
            std::vector<int> newVector;
            newVector.push_back(value);
            isAdded = isAdded && map.insert({ key, newVector }).second;
        }
        else {
            std::vector<int> set = map.at(key);
            map.at(key).push_back(value);
        }

        return isAdded;
    }

    template <typename T, typename U, typename Hash, typename Pred, typename Alloc>
    static std::unordered_set<T> getKeySetFromMap(std::unordered_map<T, U, Hash, Pred, Alloc>& map) {
        std::unordered_set<T> keySet;
        for (auto const& pair : map) {
            keySet.insert(pair.first);
        }
        return keySet;
    }

    template <typename T, typename U, typename Hash, typename Pred, typename Alloc>
    static std::tuple<std::vector<T>, std::vector<U>> convertMapToVectorTuple(std::unordered_map<T, U, Hash, Pred, Alloc>& map) {
        std::vector<T> firstColumn;
        std::vector<U> secondColumn;

        for (auto const& pair : map) {
            firstColumn.push_back(pair.first);
            secondColumn.push_back(pair.second);
        }

        return { firstColumn, secondColumn };
    }

    static std::tuple<std::vector<int>, std::vector<int>> convertSetPairsToVectorTuple(std::unordered_set<std::pair<int, int>, hashFunction>& set) {
        std::vector<int> firstColumn;
        std::vector<int> secondColumn;

        for (auto const& pair : set) {
            firstColumn.push_back(pair.first);
            secondColumn.push_back(pair.second);
        }

        return { firstColumn, secondColumn };
    }

    template <typename T>
    static std::unordered_set<std::pair<T, T>, PKBUtil::hashFunction> convertVectorTupleToSetPairs(std::vector<T> firstEntities, std::vector<T> secondEntities) {
        std::unordered_set<std::pair<T, T>, PKBUtil::hashFunction> result;

        for (int i = 0; i < firstEntities.size(); i++) {
            std::pair<T, T> pair;
            pair = std::make_pair(firstEntities[i], secondEntities[i]);
            result.insert(pair);
        }
        
        return result;
    }
}
