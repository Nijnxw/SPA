file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
			   "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*/*.cpp"
)
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
				  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
				  "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*/*.h" 
				  "${CMAKE_CURRENT_SOURCE_DIR}/src/PQL/*/*.hpp"
)
add_executable(unit_testing ${srcs})

target_link_libraries(unit_testing spa)

