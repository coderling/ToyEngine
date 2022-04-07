add_library(Platform OBJECT)

target_compile_definitions(Platform
	PUBLIC
		"$<BUILD_INTERFACE:Engine_EXPORTS>"
)

add_subdirectory(windows)

target_include_directories(Platform
PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
		"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
		"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/interface>"
)


set(public_headers
	"${CMAKE_CURRENT_SOURCE_DIR}/Platform.hpp"
)

set_target_properties(Platform
	PROPERTIES
		PUBLIC_HEADER "${public_headers}"
)

target_link_libraries(Platform PRIVATE Components)
