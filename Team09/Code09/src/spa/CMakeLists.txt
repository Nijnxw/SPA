file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(spa ${srcs} ${headers}
src/models/EntityType.h
src/models/Query.h
src/models/QueryClause.h
src/models/QueryArgument.h
src/models/QueryPatternClause.h
src/models/Query.cpp
src/models/QueryArgument.cpp
src/models/QueryClause.cpp
src/models/QueryPatternClause.cpp
src/models/QueryClauseTable.cpp
src/models/QueryClauseTable.h
src/models/QueryRelationType.h
src/models/QuerySuchThatClause.cpp
src/models/QuerySuchThatClause.h
src/util/QueryUtils.cpp
src/util/QueryUtils.h
src/util/RPN.h
src/util/RPN.cpp
src/util/RPNToken.cpp
src/util/RPNToken.h
src/simple_parser/Lexer.cpp
src/simple_parser/Lexer.h
src/simple_parser/Token.cpp
src/simple_parser/Token.h
src/simple_parser/DesignExtractor.cpp
src/simple_parser/DesignExtractor.h
src/models/QueryClauseTable.h
src/models/QueryClauseTable.h
src/models/AssignStatement.cpp
src/models/AssignStatement.h
src/pkb/stores/EntityStore.cpp
src/pkb/stores/EntityStore.h
src/pkb/stores/FollowsStore.cpp
src/pkb/stores/FollowsStore.h
src/pkb/stores/ModifiesStore.cpp
src/pkb/stores/ModifiesStore.h
src/pkb/stores/ParentStore.cpp
src/pkb/stores/ParentStore.h
src/pkb/stores/UsesStore.cpp
src/pkb/stores/UsesStore.h
src/pkb/PKB.cpp
src/pkb/PKB.h
src/pkb/util/PKBUtil.cpp 
src/models/simple_parser/NodeType.h
src/models/simple_parser/BinaryOperator.h
src/models/simple_parser/Node.h
src/models/simple_parser/Node.cpp
src/models/simple_parser/AST.h
src/models/simple_parser/AST.cpp
src/models/simple_parser/ProcedureNode.h
src/models/simple_parser/ProcedureNode.cpp
src/models/simple_parser/StmtNode.h
src/models/simple_parser/StmtNode.cpp
src/models/simple_parser/IoNodes.h
src/models/simple_parser/IoNodes.cpp
src/models/simple_parser/ExprNodes.h
src/models/simple_parser/ExprNodes.cpp)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


