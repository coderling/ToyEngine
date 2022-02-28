cmake_minimum_required(VERSION 3.20)
project(hello_window)

set(CMAKE_CXX_STANDARD 20)

find_package(ToyEngine REQUIRED CONFIG) 

add_executable(HelloWindow test-hello-window.cpp )

get_property(_location TARGET ToyEngine::Engine PROPERTY LOCATION)
message("KKK:${_location}")
 cmake_path(GET _location PARENT_PATH _dll_path)
message("KKK:${_dll_path}")
if(WIN32)
set_property(TARGET HelloWindow PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${_dll_path})
endif()

target_link_libraries(HelloWindow PRIVATE ToyEngine::Engine)

include(CMakePrintHelpers)
cmake_print_properties(
	TARGETS
		ToyEngine::Engine
	PROPERTIES
		LOCATION
		IMPORTED_IMPLIB_DEBUG
		IMPORTED_LOCATION_DEBUG
		_IMPORT_PREFIX
)
