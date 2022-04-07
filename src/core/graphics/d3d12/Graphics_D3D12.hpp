#pragma once

#include "IGraphics.hpp"
#include <memory>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class Graphics final : public IGraphics
	{
	public:
		int Initialize()  override;
	
		IDevice* GetDevice() const noexcept override { return device.Get(); }
		ISwapChain* GetSwapChain() const noexcept override { return swapchain.get(); }
		IGraphicsCommandQueue* GetCommandQueue() const noexcept override { return command_queue.get(); }
		void WaitForGpu() override;
	protected:
		void Finalize() override;
	private:
		ComPtr<IDevice> device;
		std::unique_ptr<ISwapChain> swapchain;
		std::unique_ptr<IGraphicsCommandQueue> command_queue;
		ComPtr<IDeviceCommandAllocator> common_allocator;

		//synchronization
		UINT frame_index = 0;
		HANDLE fence_event;
		ComPtr<ID3D12Fence> fence;
		UINT64 fence_value;
	};
}
