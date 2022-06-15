#pragma once
#include <d3d12.h>
#include <stdint.h>
#include <IObject.hpp>

namespace Toy::Graphics
{
class DescriptorHeapHandle final : public Engine::NoCopy
{
    D3D12_CPU_DESCRIPTOR_HANDLE cpu_base_address;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_base_address;
    uint32_t num_handles;

   public:
    DescriptorHeapHandle() noexcept;

    // move
    DescriptorHeapHandle(DescriptorHeapHandle&& rhs) noexcept;
    // assigned move
    DescriptorHeapHandle& operator=(DescriptorHeapHandle&& rhs) noexcept;

    bool IsNull() const noexcept;

    bool IsShaderVisiable() const noexcept;
};

class IDescriptorAllocator
{
   public:
   virtual DescriptorHeapHandle Allocate(size_t count) = 0;
   virtual void Free(const DescriptorHeapHandle& handle) = 0;
};

}  // namespace Toy::Graphics