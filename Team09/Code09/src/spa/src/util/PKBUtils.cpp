#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace PKBUtils {
    struct pairHashFunction {
        template <typename T, typename U>
        std::size_t operator()(const std::pair<T, U>& x) const
        {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
        }
    };

    template <typename T>
    static std::unordered_set<T> unorderedSetIntersection(const std::unordered_set<T>& set1, const std::unordered_set<T>& set2, bool earlyTermination = false) {
        std::unordered_set<T> resultSet;

        if (set2.size() < set1.size()) {
            return unorderedSetIntersection(set2, set1, earlyTermination);
        }

        for (const auto& ele : set1) {
            if (set2.find(ele) != set2.end()) {
                resultSet.insert(ele);
                if (earlyTermination) {
                    break;
                }
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

    static std::unordered_set<int> getValueSetFromMapWithSet(std::unordered_map<int, std::unordered_set<int>>& map) {
        std::unordered_set<int> valueSet;
        for (auto const& pair : map) {
            for (auto const& element : pair.second) {
                valueSet.insert(element);
            }
        }
        return valueSet;
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

    static std::tuple<std::vector<int>, std::vector<int>> convertMapWithSetToVectorTuple(std::unordered_map<int, std::unordered_set<int>>& map) {
        std::vector<int> firstColumn;
        std::vector<int> secondColumn;

        for (auto const& pair : map) {
            for (auto const& element : pair.second) {
                firstColumn.push_back(pair.first);
                secondColumn.push_back(element);
            }
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
    static std::unordered_set<std::pair<T, T>, PKBUtils::pairHashFunction> convertVectorTupleToSetPairs(std::vector<T> firstEntities, std::vector<T> secondEntities) {
        std::unordered_set<std::pair<T, T>, PKBUtils::pairHashFunction> result;

        for (int i = 0; i < firstEntities.size(); i++) {
            std::pair<T, T> pair;
            pair = std::make_pair(firstEntities[i], secondEntities[i]);
            result.insert(pair);
        }

        return result;
    }

    static std::unordered_set<int> getEqualPairs(const std::vector<int>& first, const std::vector<int>& second) {
        std::unordered_set<int> result;
        for (int index = 0; index < first.size(); index++) {
            if (first[index] == second[index]) {
                result.insert(first[index]);
            }
        }
        return result;
    }

    template <typename T>
    static std::vector<T> convertUnorderedSetToVector(std::unordered_set<T> set) {
        std::vector<T> vector;
        vector.reserve(set.size());
        for (auto it = set.begin(); it != set.end(); ) {
            vector.push_back(std::move(set.extract(it++).value()));
        }
        return vector;
    }

    template <typename T>
    static std::tuple<std::vector<T>, std::vector<T>> computeCartesianProduct(std::vector<T> vec1, std::vector<T> vec2, bool earlyTermination = false) {
        std::vector<T> resVec1;
        std::vector<T> resVec2;
        for (const auto& entry1 : vec1) {
            for (const auto& entry2 : vec2) {
                resVec1.push_back(entry1);
                resVec2.push_back(entry2);
                if (earlyTermination)
                    return { resVec1, resVec2 };
            }
        }
        return { resVec1, resVec2 };
    }
}
