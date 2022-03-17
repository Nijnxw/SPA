#include "catch.hpp"
#include "util/PKBUtils.cpp"

TEST_CASE("PKBUtil Helper Functions") {

		SECTION("unorderedSetIntersection(set1, set2) positive query") {
			std::unordered_set<int> setOne; // 1, 2, 3
			std::unordered_set<int> setTwo; // 2, 3, 4, 5

			setOne.insert(1);
			setOne.insert(2);
			setOne.insert(3);

			setTwo.insert(2);
			setTwo.insert(3);
			setTwo.insert(4);
			setTwo.insert(5);

			std::unordered_set<int> res = PKBUtils::unorderedSetIntersection(setOne, setTwo);
			std::unordered_set<int> expectedSet = { 2, 3 };
			REQUIRE(res == expectedSet);
		}

		SECTION("addToMapWithSet(map, key, value) positive query when key does not exist") {
			std::unordered_map<int, std::unordered_set<int>> map;
			
			bool isAdded = PKBUtils::addToMapWithSet(map, 1, 2);
			REQUIRE(isAdded == true);

			std::unordered_map<int, std::unordered_set<int>> expectedMap;
			std::unordered_set<int> expectedSet = { 2 };
			expectedMap.insert({ 1, expectedSet });
			REQUIRE(map == expectedMap);
		}

		SECTION("addToMapWithSet(map, key, value) positive query when key exists") {
			std::unordered_map<int, std::unordered_set<int>> map;
			std::unordered_set<int> set = { 2 };
			map.insert({ 1, set });

			bool isAdded = PKBUtils::addToMapWithSet(map, 1, 3);
			REQUIRE(isAdded == true);

			std::unordered_map<int, std::unordered_set<int>> expectedMap;
			std::unordered_set<int> expectedSet = { 2, 3 };
			expectedMap.insert({ 1, expectedSet });
			REQUIRE(map == expectedMap);
		}

		SECTION("addToMapWithVector(map, key, value) positive query when key does not exist") {
			std::unordered_map<int, std::vector<int>> map;

			bool isAdded = PKBUtils::addToMapWithVector(map, 1, 2);
			REQUIRE(isAdded == true);

			std::unordered_map<int, std::vector<int>> expectedMap;
			std::vector<int> expectedVector = { 2 };
			expectedMap.insert({ 1, expectedVector });
			REQUIRE(map == expectedMap);
		}

		SECTION("addToMapWithVector(map, key, value) positive query when key exists") {
			std::unordered_map<int, std::vector<int>> map;
			std::vector<int> vector = { 2 };
			map.insert({ 1, vector });

			bool isAdded = PKBUtils::addToMapWithVector(map, 1, 3);
			REQUIRE(isAdded == true);

			std::unordered_map<int, std::vector<int>> expectedMap;
			std::vector<int> expectedVector = { 2, 3 };
			expectedMap.insert({ 1, expectedVector });
			REQUIRE(map == expectedMap);
		}

		SECTION("getKeySetFromMap(map) positive query when key does not exist") {
			std::unordered_map<int, int> map;

			std::unordered_set<int> set = PKBUtils::getKeySetFromMap(map);

			std::unordered_set<int> expectedSet;
			REQUIRE(set == expectedSet);
		}

		SECTION("getKeySetFromMap(map) positive query when key exists") {
			std::unordered_map<int, int> map;
			map.insert({ 1, 2 });

			std::unordered_set<int> set = PKBUtils::getKeySetFromMap(map);

			std::unordered_set<int> expectedSet = { 1 };
			REQUIRE(set == expectedSet);
		}

		SECTION("convertMapToVectorTuple positive query when key does not exist") {
			std::unordered_map<int, int> map;

			std::tuple<std::vector<int>, std::vector<int>> tuple = PKBUtils::convertMapToVectorTuple(map);

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			std::tuple<std::vector<int>, std::vector<int>> expectedTuple = { firstColumn, secondColumn };
			REQUIRE(tuple == expectedTuple);
		}

		SECTION("convertMapToVectorTuple positive query when key exists") {
			std::unordered_map<int, int> map;
			map.insert({ 1, 2 });

			std::tuple<std::vector<int>, std::vector<int>> tuple = PKBUtils::convertMapToVectorTuple(map);

			std::vector<int> firstColumn = { 1 };
			std::vector<int> secondColumn = { 2 };

			std::tuple<std::vector<int>, std::vector<int>> expectedTuple = { firstColumn, secondColumn };
			REQUIRE(tuple == expectedTuple);
		}

		SECTION("convertSetPairsToVectorTuple positive query when key does not exist") {
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set;

			std::tuple<std::vector<int>, std::vector<int>> tuple = PKBUtils::convertSetPairsToVectorTuple(set);

			std::vector<int> firstColumn;
			std::vector<int> secondColumn;

			std::tuple<std::vector<int>, std::vector<int>> expectedTuple = { firstColumn, secondColumn };
			REQUIRE(tuple == expectedTuple);
		}

		SECTION("convertSetPairsToVectorTuple positive query when key exists") {
			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> set;

			std::pair<int, int> pair;
			pair = std::make_pair(1, 2);
			set.insert(pair);

			std::tuple<std::vector<int>, std::vector<int>> tuple = PKBUtils::convertSetPairsToVectorTuple(set);

			std::vector<int> firstColumn = { 1 };
			std::vector<int> secondColumn = { 2 };

			std::tuple<std::vector<int>, std::vector<int>> expectedTuple = { firstColumn, secondColumn };
			REQUIRE(tuple == expectedTuple);
		}

		SECTION("convertVectorTupleToSetPairs positive query when key exists") {
			std::vector<int> firstColumn = { 1 };
			std::vector<int> secondColumn = { 2 };

			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> tuple = 
				PKBUtils::convertVectorTupleToSetPairs(firstColumn, secondColumn);

			std::unordered_set<std::pair<int, int>, PKBUtils::pairHashFunction> expectedTuple;

			std::pair<int, int> pair;
			pair = std::make_pair(1, 2);
			expectedTuple.insert(pair);

			REQUIRE(tuple == expectedTuple);
		}

		SECTION("convertUnorderedSetToVector positive query") {
			std::unordered_set<int> firstSet = { 1 };
			std::unordered_set<int> secondSet = { 1 };

			std::vector<int> firstVector = PKBUtils::convertUnorderedSetToVector(firstSet);
			std::vector<int> secondVector = PKBUtils::convertUnorderedSetToVector(secondSet);

			REQUIRE(firstVector == secondVector);
		}

		SECTION("computeCartesianProduct positive query") {
			std::vector<std::string> firstVec = { "1", "2" };
			std::vector<std::string> secondVec = { "3", "4" };

			std::tuple<std::vector<std::string>, std::vector<std::string>> res = PKBUtils::computeCartesianProduct(firstVec, secondVec);

			std::vector<std::string> expectedFirstVec = { "1", "1", "2", "2" };
			std::vector<std::string> expectedSecondVec = { "3", "4", "3", "4" };

			REQUIRE(std::get<0>(res) == expectedFirstVec);
			REQUIRE(std::get<1>(res) == expectedSecondVec);
		}
}
