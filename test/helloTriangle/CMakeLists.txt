cmake_minimum_required(VERSION 3.20)
project(hello_triangle)

set(CMAKE_CXX_STANDARD 20)

find_package(ToyEngine REQUIRED CONFIG) 

add_executable(helloTriangle "test-hello-triangle.cpp")
target_sources(helloTriangle 
	PRIVATE 
					"RenderLogic.hpp"
)

target_include_directories(helloTriangle
    PUBLIC       "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

target_link_libraries(helloTriangle PRIVATE ToyEngine::Engine)

# debug args
set_target_properties(helloTriangle PROPERTIES 
    VS_DEBUGGER_COMMAND "debug_command"
    VS_DEBUGGER_COMMAND_ARGUMENTS "debug_arguments")

# copy debug dll to debug run dir
get_property(_location TARGET ToyEngine::Engine PROPERTY LOCATION)

string(
	APPEND copy_cmd
	"$<IF:$<CONFIG:Debug>,"
		"${CMAKE_COMMAND};-E;copy_if_different;${_location};${CMAKE_CURRENT_BINARY_DIR},"
	">"
)

add_custom_command(TARGET helloTriangle
	POST_BUILD
	COMMAND "${copy_cmd}"
	COMMAND_EXPAND_LISTS
)

