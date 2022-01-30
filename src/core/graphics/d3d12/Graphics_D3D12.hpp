#pragma once

#include "Def.hpp"
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
		ISwapChain* GetSwapChain() const noexcept { return swapchain.Get(); }
	
	private:
		ComPtr<IDevice> device;
		ComPtr<ISwapChain> swapchain;
		ComPtr<IDeviceCommandQueue> command_queue;
	};
}
