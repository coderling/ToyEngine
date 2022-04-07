#include "SwapChain_D3D12.hpp"
#include "../../interface/IApp.hpp"
#include "../../interface/GlobalEnvironment.hpp"
#include "Utility.hpp"
#include "../GraphicsDef.hpp"
#include "IGraphics.hpp"
#include "IGraphicsCommandQueue.hpp"

using namespace Toy::Graphics;

int SwapChain::Initialize(IDXGIFactory* factory)
{
	DXGI_SWAP_CHAIN_DESC1 swap_desc;
	const auto p_env = Toy::Engine::IApp::env;
	const auto args = p_env->GetApp()->GetArgs();
	swap_desc.Width = args->screen_width;
	swap_desc.Height = args->screen_height;
	swap_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc.BufferCount = args->frame_count;
	swap_desc.SampleDesc.Count = 1;
	swap_desc.SampleDesc.Quality = 0;
	swap_desc.Scaling = DXGI_SCALING_NONE;
	swap_desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
	fsSwapChainDesc.Windowed = TRUE;

	ComPtr<IDXGIFactory4> factory4;
	ComPtr<IDXGISwapChain1> tswapchain;
	if (SUCCEEDED(factory->QueryInterface(MY_IID_PPV_ARGS(&factory4))))
	{
		auto command_queue = p_env->GetGraphics()->GetCommandQueue()->GetDeviceQueue();
		HWND hwnd = reinterpret_cast<HWND>(p_env->GetApp()->GetHwnd());
		ASSERT_SUCCEEDED(factory4->CreateSwapChainForHwnd(command_queue, hwnd, &swap_desc, &fsSwapChainDesc, nullptr, &tswapchain));
		tswapchain.As(&swapchain);
	}
	return 0;
}

void SwapChain::Present()
{
	swapchain->Present(1, 0);
}

void SwapChain::Resize(uint32_t width, uint32_t height)
{

}

void SwapChain::SetFullScreen(bool state)
{

}

uint32_t SwapChain::GetCurrentBackBufferIndex()
{
	return swapchain->GetCurrentBackBufferIndex();
}

void SwapChain::OnDestroy()
{

}
