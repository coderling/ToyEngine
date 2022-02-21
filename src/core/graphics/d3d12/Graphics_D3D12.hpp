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
		void Tick() override;
		void Finalize() override;
		void Destroy() override;
	
		IDevice* GetDevice() const noexcept override { return device.Get(); }
		ISwapChain* GetSwapChain() const noexcept override { return swapchain.get(); }
		IGraphicsCommandQueue* GetCommandQueue() override { return command_queue.get(); }
	
	private:
		ComPtr<IDevice> device;
		std::unique_ptr<ISwapChain> swapchain;
		std::unique_ptr<IGraphicsCommandQueue> command_queue;
		ComPtr<IDeviceCommandAllocator> common_allocator;
	};
}
