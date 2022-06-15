target_sources(Graphics
	 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/UploadBuffer_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/GPUResource_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/Graphics_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/SwapChain_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/GraphicsCommandQueue_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/GraphicsCommandQueue_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/DescriptorMemoryMgr.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/PipelineState.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/Fence_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/FrameResource_D3D12.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/DescriptorHeap.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/DXCCompiler.cpp"
					"${CMAKE_CURRENT_SOURCE_DIR}/GraphicsCommandList_D3D12.cpp")

