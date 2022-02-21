add_library(Common OBJECT)
target_sources(Common
	PRIVATE "App.cpp"
)

target_include_directories(Common
	PUBLIC "${PROJECT_SOURCE_DIR}/src/core/interface"
				  "${PROJECT_SOURCE_DIR}/src/common"
)