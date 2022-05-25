cmake_minimum_required(VERSION 3.20)
project(apiTest)

set(CMAKE_CXX_STANDARD 20)
find_package(ToyEngine REQUIRED CONFIG) 

file(GLOB source LIST_DIRECTORIES false src/*)
file(GLOB include LIST_DIRECTORIES false include/*)

set(all_source ${source} ${include})

add_executable(apiTest ${all_source})

target_link_libraries(apiTest PRIVATE ToyEngine::Engine test_utility)

# copy debug dll to debug run dir
get_property(_location TARGET ToyEngine::Engine PROPERTY LOCATION)

string(
	APPEND copy_cmd
	"$<IF:$<CONFIG:Debug>,"
		"${CMAKE_COMMAND};-E;copy_if_different;${_location};${CMAKE_CURRENT_BINARY_DIR},"
	">"
)

add_custom_command(TARGET apiTest
	POST_BUILD
	COMMAND "${copy_cmd}"
	COMMAND_EXPAND_LISTS
)

