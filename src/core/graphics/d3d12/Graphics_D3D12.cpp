#include <wrl.h>

#include "Utility.hpp"
#include "../../interface/IApp.hpp"
#include "../../interface/GlobalEnvironment.hpp"
#include "Graphics_D3D12.hpp"
#include "GraphicsCommandQueue_D3D12.hpp"
#include "SwapChain_D3D12.hpp"

using namespace Toy::Graphics;
using namespace Microsoft::WRL;

std::unique_ptr<IGraphics> graphics;

IGraphics* IGraphics::GetInstance()
{
	if (graphics == nullptr)
	{
		graphics = std::make_unique<Graphics>();
	}
	return graphics.get();
}

int Graphics::Initialize()
{
	UINT dxg_flactory_flags = 0;
#if defined(_DEBUG)
	ComPtr<ID3D12Debug> debug_controller;
	if (SUCCEEDED(D3D12GetDebugInterface(MY_IID_PPV_ARGS(&debug_controller))))
	{
		debug_controller->EnableDebugLayer();

		dxg_flactory_flags |= DXGI_CREATE_FACTORY_DEBUG;
	}
#endif

	ComPtr<IDXGIFactory7> factory;
	ASSERT_SUCCEEDED(CreateDXGIFactory2(dxg_flactory_flags, MY_IID_PPV_ARGS(&factory)));

	if (IApp::env->GetApp()->GetArgs()->use_wrap_device)
	{
		ComPtr<IDXGIAdapter> wrap_adapter;
		ASSERT_SUCCEEDED(factory->EnumWarpAdapter(MY_IID_PPV_ARGS(&wrap_adapter)));
	
		ASSERT_SUCCEEDED(D3D12CreateDevice(wrap_adapter.Get(), D3D_FEATURE_LEVEL_11_0, MY_IID_PPV_ARGS(&device)));
	}
	else
	{
		ComPtr<IDXGIAdapter4> hardware_adapter;
		for (
			UINT adapterIndex = 0;
			SUCCEEDED(factory->EnumAdapterByGpuPreference(
				adapterIndex,
				DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
				MY_IID_PPV_ARGS(&hardware_adapter)));
			++adapterIndex
			)
		{
			DXGI_ADAPTER_DESC1 desc;
			hardware_adapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				continue;
			}

			if (SUCCEEDED(D3D12CreateDevice(hardware_adapter.Get(), D3D_FEATURE_LEVEL_11_0, MY_IID_PPV_ARGS(&device))))
			{
				break;
			}
		}
	}


	D3D12_COMMAND_QUEUE_DESC queue_desc = {};
	queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	command_queue =  std::make_unique<GraphicsCommandQueue>(&queue_desc);

	auto psw = std::make_unique<SwapChain>();
	psw->Initialize(factory.Get());
	swapchain = std::move(psw);

	ASSERT_SUCCEEDED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, MY_IID_PPV_ARGS(&common_allocator)));
	// todo descriptor heaps
	return 0;
}

void Graphics::Finalize()
{
}
