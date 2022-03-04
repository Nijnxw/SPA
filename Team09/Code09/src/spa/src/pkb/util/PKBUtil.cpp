#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace PKBUtil {
    struct pairHashFunction {
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U>& x) const
        {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
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

    template <typename T>
    static bool addToMapWithSet(std::unordered_map<T, std::unordered_set<T>>& map, const T key, const T value) {
        bool isAdded = true;

        if (map.count(key) <= 0) {
            std::unordered_set<T> newSet;
            isAdded = isAdded && newSet.insert(value).second;
            isAdded = isAdded && map.insert({ key, newSet }).second;
        }
        else {
            std::unordered_set<T>& set = map[key];
            isAdded = isAdded && set.insert(value).second;
        }

        return isAdded;
    }

    template <typename T>
    static bool addToMapWithVector(std::unordered_map<T, std::vector<T>>& map, const T key, const T value) {
        bool isAdded = true;

        if (map.count(key) <= 0) {
            std::vector<T> newVector;
            newVector.push_back(value);
            isAdded = isAdded && map.insert({ key, newVector }).second;
        }
        else {
            std::vector<T> set = map.at(key);
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

    template <typename T>
    static std::tuple<std::vector<T>, std::vector<T>> convertSetPairsToVectorTuple(std::unordered_set<std::pair<T, T>, pairHashFunction>& set) {
        std::vector<T> firstColumn;
        std::vector<T> secondColumn;

        for (auto const& pair : set) {
            firstColumn.push_back(pair.first);
            secondColumn.push_back(pair.second);
        }

        return { firstColumn, secondColumn };
    }

    template <typename T>
    static std::unordered_set<std::pair<T, T>, PKBUtil::pairHashFunction> convertVectorTupleToSetPairs(std::vector<T> firstEntities, std::vector<T> secondEntities) {
        std::unordered_set<std::pair<T, T>, PKBUtil::pairHashFunction> result;

        for (int i = 0; i < firstEntities.size(); i++) {
            std::pair<T, T> pair;
            pair = std::make_pair(firstEntities[i], secondEntities[i]);
            result.insert(pair);
        }
        
        return result;
    }
}
