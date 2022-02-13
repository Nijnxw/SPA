file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.cpp"
   			   "${CMAKE_CURRENT_SOURCE_DIR}/src/evaluators/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/util/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/Tokeniser/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/Parser/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.cpp"
)
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.h"
   			   "${CMAKE_CURRENT_SOURCE_DIR}/src/evaluators/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/util/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/Tokeniser/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/Parser/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.h"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.h"

			   "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/models/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/pkb/util/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/tokeniser/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/Parser/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/simple_parser/*.hpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.hpp"
)

add_executable(unit_testing ${srcs})

target_link_libraries(unit_testing spa)
