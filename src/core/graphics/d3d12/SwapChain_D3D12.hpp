#pragma once

#include "ISwapChain.hpp"

#include <dxgi1_6.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class SwapChain final: public ISwapChain
	{
	public:
		int Initialize(IDXGIFactory* factory);
		void Present() override;
		void Resize(uint32_t width, uint32_t height) override;
		void SetFullScreen(bool state) override;
		bool IsFullScreen() const noexcept override { return is_fullscreen; }
	protected:
		void OnDestroy() override;
	private:
		bool is_fullscreen;
		ComPtr<IDXGISwapChain3> swapchain = nullptr;
	};
}