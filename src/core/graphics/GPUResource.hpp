#pragma once

#include <wrl.h>
#include "GraphicsDef.hpp"
#include "IObject.hpp"

using namespace Toy::Engine;
using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class GPUResource : public IObject
	{
	public:
		GPUResource();
		virtual void GPUResource() { Destroy(); }
		IDeviceResource* operator->();
		const IDeviceResource* operator->() const;
		IDeviceResource* GetResource();
		const IDeviceResource* GetResource() const;
		IDeviceResource** GetAddressOf();
		GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const;
		void Destroy() override;
protected:
	ComPtr<IDeviceResource> p_resource;
	D3D12_RESOURCE_STATES usage_state;
	D3D12_RESOURCE_STATES transitioning_state;
	D3D12_GPU_VIRTUAL_ADDRESS gpu_virtual_address;
	};
}