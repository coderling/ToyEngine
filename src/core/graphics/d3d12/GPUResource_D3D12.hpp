#pragma once

#include <wrl.h>
#include "IGPUResource.hpp"

using namespace Toy::Engine;
using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class GPUResource : public IGPUResource
	{
	public:
		GPUResource();
		virtual ~GPUResource() { Destroy(); }
		IDeviceResource* operator->();
		const IDeviceResource* operator->() const;
		IDeviceResource* GetResource() override;
		const IDeviceResource* GetResource() const override;
		IDeviceResource** GetAddressOf() override;
		GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const override;
		void Destroy() override;
protected:
	ComPtr<IDeviceResource> p_resource;
	D3D12_RESOURCE_STATES usage_state;
	D3D12_RESOURCE_STATES transitioning_state;
	D3D12_GPU_VIRTUAL_ADDRESS gpu_virtual_address;
	};
}