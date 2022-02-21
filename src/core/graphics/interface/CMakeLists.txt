add_library(GraphicsInterface INTERFACE)

target_sources(GraphicsInterface
	INTERFACE "IFrameResource.hpp"
						"IGPUResource.hpp"
						"IGraphics.hpp"
						"IGraphicsCommandList.hpp"
						"IGraphicsCommandQueue.hpp"
						"IPipeline.hpp"
						"IRenderTexture.hpp"
						"ISwapChain.hpp"
						"IUploadBuffer.hpp"
)