file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs}
src/util/TestRPN.cpp
src/util/TestRPNToken.cpp
src/simple_parser/TestLexer.cpp
src/util/TestQueryClauseTable.cpp
src/pkb/TestUsesStore.cpp
src/pkb/TestModifiesStore.cpp
src/util/TestQueryUtils.cpp "src/models/TestAST.cpp")

target_link_libraries(unit_testing spa)

