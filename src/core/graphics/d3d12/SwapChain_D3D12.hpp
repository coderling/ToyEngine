#pragma once

#include "ISwapChain.hpp"

#include <dxgi1_6.h>

namespace Toy::Graphics
{
	class SwapChain final: ISwapChain
	{
	public:
		int Initialize(IDXGIFactory* factory);
		void Present() override;
		void Resize(uint32_t width, uint32_t height) override;
		bool IsFullScreen() const noexcept override { return is_fullscreen; }

	private:
		bool is_fullscreen;
	};
}