#pragma once

#include <wrl.h>
#include "IGPUResource.hpp"

using namespace Toy::Engine;
using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class GPUResource : public IGPUResource
{
    friend class GraphicsCommandlist;
    friend class UploadBuffer;

   public:
    GPUResource();
    IDeviceResource* GetResource() override;
    const IDeviceResource* GetResource() const override;
    IDeviceResource** GetAddressOf() override;
    GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const override;
    void Release() override;

   protected:
    void OnDestroy() override;
    ComPtr<IDeviceResource> p_resource;
    D3D12_RESOURCE_STATES usage_state;
    D3D12_RESOURCE_STATES transitioning_state;
    D3D12_GPU_VIRTUAL_ADDRESS gpu_virtual_address;
};
}  // namespace Toy::Graphics