add_library(Components OBJECT)
target_sources(Components
	PRIVATE "SystemMgr.cpp"
					"App.cpp"
)
target_include_directories(Components
	PUBLIC 
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/components>"
				"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/interface>"
)
target_link_libraries(Components PRIVATE Graphics Common)
