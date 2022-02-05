file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs}
src/util/TestRPN.cpp
src/util/TestRPNToken.cpp
src/simple_parser/TestLexer.cpp
src/util/TestQueryClauseTable.cpp
src/pkb/TestEntityStore.cpp
src/pkb/TestFollowsStore.cpp
src/pkb/TestParentStore.cpp
src/pkb/TestUses.cpp
src/pkb/TestModifies.cpp
src/util/TestQueryUtils.cpp
src/models/TestAST.cpp
src/simple_parser/TestParseProcedure.cpp
src/simple_parser/TestParseRead.cpp)

target_link_libraries(unit_testing spa)

