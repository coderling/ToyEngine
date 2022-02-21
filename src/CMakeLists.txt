add_library(Engine)

add_subdirectory(core)
add_subdirectory(platform)

target_link_libraries(Engine PUBLIC Common Graphics Platform)

target_include_directories(Engine
	PRIVATE "${PROJECT_SOURCE_DIR}/src/core/interface"
						"${PROJECT_SOURCE_DIR}/src/core/graphics/interface"
	INTERFACE "${PROJECT_SOURCE_DIR}/src/include"
)

install(TARGETS Engine DESTINATION ${_Install_path})
