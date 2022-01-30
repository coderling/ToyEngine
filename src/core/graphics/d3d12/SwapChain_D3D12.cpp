#include "SwapChain_D3D12.hpp"
#include "IApp.hpp"
#include "Utility.hpp"

#include <wrl.h>

using namespace Microsoft::WRL;
using namespace Toy::Graphics;

int SwapChain::Initialize(IDXGIFactory* factory)
{
	DXGI_SWAP_CHAIN_DESC1 swap_desc;
	const auto p_env = Toy::Engine::IApp::env;
	const auto& args = p_env->app->GetArgs();
	swap_desc.BufferCount = args.frame_count;
	swap_desc.Width = args.screen_width;
	swap_desc.Height = args.screen_height;
	swap_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_desc.SampleDesc.Count = 1;

	ComPtr<IDXGISwapChain1> swapchain;

	return 0;
}
