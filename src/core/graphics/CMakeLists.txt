add_library(Graphics OBJECT)

target_sources(Graphics 
	PRIVATE	
					"Pipeline.cpp"
					"PipelineFragment.cpp")

target_compile_definitions(Graphics
	PUBLIC
		"$<BUILD_INTERFACE:Engine_EXPORTS>"
)

add_subdirectory(d3d12)

target_include_directories(Graphics
    PUBLIC       "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>"
						"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
						"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
						"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/interface>"
						"$<BUILD_INTERFACE:${DXCFolder}>"
)
message("dxcf:" ${PROJECT_SOURCE_DIR}/../External/dxc )
message("dxcf:" ${DXCFolder})
link_libraries(Graphics, DXCFolder_Lib)
target_link_libraries(Graphics PRIVATE Common ${d3d12_libs} )

set(public_headers
	"${CMAKE_CURRENT_SOURCE_DIR}/PipelineFragment.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/GraphicsDef.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IPipelineFragmentHandler.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IFrameResource.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/ISwapChain.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IGPUResource.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IGraphicsCommandQueue.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IGraphicsCommandList.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IGraphics.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IPipeline.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/interface/IUploadBuffer.hpp"
)

set_target_properties(Graphics
	PROPERTIES
		PUBLIC_HEADER "${public_headers}"
)
