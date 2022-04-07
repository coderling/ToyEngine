#include <wrl.h>
#include "GPUResource_D3D12.hpp"
#include "../../interface/GlobalEnvironment.hpp"

using namespace Toy::Graphics;
using namespace Microsoft::WRL;

GPUResource::GPUResource() 
	: gpu_virtual_address(GPU_VIRTUAL_ADDRESS_NULL ),
	usage_state(D3D12_RESOURCE_STATE_COMMON),
	transitioning_state((D3D12_RESOURCE_STATES)-1) {}

void GPUResource::OnDestroy()
{
	p_resource = nullptr;
	gpu_virtual_address = GPU_VIRTUAL_ADDRESS_NULL;
}

IDeviceResource* GPUResource::GetResource()
{
	return p_resource.Get();
}

const IDeviceResource* GPUResource::GetResource() const
{
	return p_resource.Get();
}

IDeviceResource** GPUResource::GetAddressOf()
{
	return p_resource.GetAddressOf();
}

GPU_VIRTUAL_ADDRESS GPUResource::GetGpuVirtualAddress() const
{
	return gpu_virtual_address;
}
