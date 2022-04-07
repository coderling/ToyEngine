cmake_minimum_required(VERSION 3.20)
project(test_align)

set(CMAKE_CXX_STANDARD 20)

find_package(ToyEngine REQUIRED CONFIG) 

add_executable(test_align "test-align.cpp")

target_link_libraries(test_align PRIVATE ToyEngine::Engine)

# copy debug dll to debug run dir
get_property(_location TARGET ToyEngine::Engine PROPERTY LOCATION)

string(
	APPEND copy_cmd
	"$<IF:$<CONFIG:Debug>,"
		"${CMAKE_COMMAND};-E;copy_if_different;${_location};${CMAKE_CURRENT_BINARY_DIR},"
	">"
)

add_custom_command(TARGET test_align
	POST_BUILD
	COMMAND "${copy_cmd}"
	COMMAND_EXPAND_LISTS
)

