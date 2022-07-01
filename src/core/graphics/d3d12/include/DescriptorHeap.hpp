#pragma once
#include <d3d12.h>
#include <stdint.h>
#include <IObject.hpp>
#include <vector>
#include "CommonDefines.hpp"
#include "VariableSizeAllocationsManager.hpp"

namespace Toy::Graphics
{

class IDescriptorAllocator;
class DescriptorHeapAllocationMgr;
class DecriptorSuballocationMgr;
class CPUDescriptorHeap;
class GPUDescriptorHeap;

class DescriptorHeapAllocation final
{
    static constexpr const uint16_t InvalidMgrId = 0xFFFF;

    D3D12_CPU_DESCRIPTOR_HANDLE cpu_base_address;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_base_address;
    uint32_t count;

    uint16_t allocation_mgr = InvalidMgrId;
    IDescriptorAllocator* allocator;

   public:
    NOCOPY_INPLACE(DescriptorHeapAllocation);

    DescriptorHeapAllocation() noexcept;

    // move
    DescriptorHeapAllocation(DescriptorHeapAllocation&& rhs) noexcept;
    // assigned move
    DescriptorHeapAllocation& operator=(DescriptorHeapAllocation&& rhs) noexcept;

    bool IsNull() const noexcept;

    bool IsShaderVisiable() const noexcept;
};

class IDescriptorAllocator
{
   public:
    virtual DescriptorHeapAllocation Allocate(size_t count) = 0;
    virtual void Free(const DescriptorHeapAllocation& handle) = 0;
    virtual uint16_t GetDescirptorIncSize() const = 0;
};

class DescriptorHeapAllocationMgr final
{
    Engine::VariableSizeAllocationsManager block_alloc_mgr;
    IDescriptorAllocator* allocator;

   public:
    DescriptorHeapAllocationMgr() noexcept;
};

class DecriptorSuballocationMgr final
{
    DescriptorHeapAllocationMgr alloc_mgr;

   public:
    DecriptorSuballocationMgr() noexcept;
};

class CPUDescriptorHeap final : public IDescriptorAllocator
{
    std::vector<DescriptorHeapAllocationMgr> alloc_mgrs;

   public:
    virtual DescriptorHeapAllocation Allocate(size_t count) override;
    virtual void Free(const DescriptorHeapAllocation& handle) override;
    virtual uint16_t GetDescirptorIncSize() const override;
};

class GPUDescriptorHeap final : public IDescriptorAllocator
{
    DescriptorHeapAllocationMgr static_alloc_mgr;
    DecriptorSuballocationMgr dynamic_alloc_mgr;

   public:
    virtual DescriptorHeapAllocation Allocate(size_t count) override;
    virtual void Free(const DescriptorHeapAllocation& handle) override;
    virtual uint16_t GetDescirptorIncSize() const override;
};

}  // namespace Toy::Graphics