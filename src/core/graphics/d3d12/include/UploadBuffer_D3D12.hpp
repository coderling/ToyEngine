#pragma once

#include <string>
#include "GPUResource_D3D12.hpp"
#include "IUploadBuffer.hpp"

namespace Toy::Graphics
{
class UploadBuffer : public IUploadBuffer
{
   public:
    IDeviceResource* GetResource() override;
    const IDeviceResource* GetResource() const override;
    IDeviceResource** GetAddressOf() override;
    GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const override;

    void Init(const std::string& name, size_t size) override;

    void* Map(void) override;

    void UnMap(size_t begin = 0, size_t = -1) override;
    void Release() override;

    size_t GetBufferSize() noexcept override { return buffer_size; }

   protected:
    void OnDestroy() override;
    size_t buffer_size;
    GPUResource resource;
};
}  // namespace Toy::Graphics