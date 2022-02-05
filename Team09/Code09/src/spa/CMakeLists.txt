file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.cpp"
   			   "${CMAKE_CURRENT_SOURCE_DIR}/src/evaluators/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/simple_parser/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/stores/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/util/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.cpp"
	)
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.h"
   			   "${CMAKE_CURRENT_SOURCE_DIR}/src/evaluators/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/simple_parser/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pbl/stores/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pbl/util/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.h"

			   "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" 
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/simple_parser/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/stores/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/util/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.hpp"
	)
add_library(spa ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


