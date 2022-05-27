add_library(Common OBJECT)

target_compile_definitions(Common
	PUBLIC
		"$<BUILD_INTERFACE:Engine_EXPORTS>"
)

target_sources(Common
	PRIVATE "VariableSizeAllocationsManager.cpp"
				  "STDAllocator.hpp")

target_include_directories(Common
	PUBLIC 
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/interface>"
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/common>"
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)
message(${PROJECT_SOURCE_DIR})
set(public_headers
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/AppArgs.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/GlobalEnvironment.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/IApp.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/IObject.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/ISystem.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface/IAllocator.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Align.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/FormatString.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/DebugUtility.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EngineUtility.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Logger.hpp"
)

set_target_properties(Common
	PROPERTIES
		PUBLIC_HEADER "${public_headers}"
)