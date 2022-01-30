#include "Graphics_D3D12.hpp"
#include "Utility.hpp"a
#include "IApp.hpp"
#include <wrl.h>

using namespace Toy::Graphics;
using namespace Microsoft::WRL;

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

	if (IApp::env->app->GetArgs().use_wrap_device)
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

	return 0;
}

void Graphics::Finalize()
{
	Destroy();
}

void Graphics::Tick()
{

}

void Graphics::Destroy()
{

}