#include <unordered_map>
#include <unordered_set>
#include <vector>

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class QueryUtils {
    typedef std::unordered_map<std::string, std::vector<std::string>> Table;
    typedef std::unordered_map<std::string, std::pair<std::unordered_set<int>, std::unordered_set<int>>> GroupedTable;

public:
    static Table hashJoin(const Table& firstTable, const Table& secondTable);

private:
    static std::vector<std::string> getCommonHeaders(const Table& firstTable, const Table& secondTable);

    static std::vector<std::string> getUniqueHeaders(const Table& table, const Table& secondTable);

    static GroupedTable extractCommonTuples(const std::vector<std::string>& commonHeaders,
                                            const Table& firstTable,
                                            const Table& secondTable);

    static std::string selectTupleToString(const std::vector<std::string>& headers, size_t rowNum, const Table& table);

    static void
    crossProduct(const std::unordered_set<int>& firstTupleSet, const std::unordered_set<int>& secondTupleSet,
                 std::unordered_set<std::pair<int, int>, pair_hash>& tuplePairings);

    static Table
    joinRows(const std::unordered_set<std::pair<int, int>, pair_hash>& tuplePairings, const Table& firstTable,
             const Table& secondTable, const std::vector<std::string>& commonHeaders);
};
