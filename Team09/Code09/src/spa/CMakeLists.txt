file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/models/QueryArgumentType.h src/models/Query.h src/models/QueryClause.h src/models/QueryArgument.h src/models/QueryPatternClause.h src/models/Query.cpp src/models/QueryArgument.cpp src/models/QueryClause.cpp src/models/QueryPatternClause.cpp)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


