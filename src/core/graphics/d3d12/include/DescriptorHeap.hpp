#pragma once
#include <d3d12.h>
#include <stdint.h>
#include <wrl.h>
#include <IObject.hpp>
#include <mutex>
#include <vector>
#include "CommonDefines.hpp"
#include "VariableSizeAllocationsManager.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{

class RenderDeviceD3D12;

class IDescriptorAllocator;
class DescriptorHeapAllocationMgr;
class DecriptorSuballocationMgr;
class CPUDescriptorHeap;
class GPUDescriptorHeap;

class DescriptorHeapAllocation final
{
    friend DescriptorHeapAllocationMgr;

    static constexpr const uint16_t InvalidMgrId = 0xFFFF;

    D3D12_CPU_DESCRIPTOR_HANDLE cpu_base_address;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_base_address;
    std::size_t count;
    Engine::VariableSizeAllocationsManager::OffsetSizeType block_offset;

    uint16_t allocation_mgr;
    uint16_t inc_size;
    IDescriptorAllocator* allocator;

   public:
    NOCOPY_INPLACE(DescriptorHeapAllocation);
    DescriptorHeapAllocation() noexcept;
    DescriptorHeapAllocation(IDescriptorAllocator& allocator,
                             const uint16_t& mgr_id,
                             const std::size_t& count,
                             const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle,
                             const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle) noexcept;

    ~DescriptorHeapAllocation() noexcept;
    // move
    DescriptorHeapAllocation(DescriptorHeapAllocation&& rhs) noexcept;
    // assigned move
    DescriptorHeapAllocation& operator=(DescriptorHeapAllocation&& rhs) noexcept;

    void Clear();

    bool IsNull() const noexcept;

    bool IsShaderVisiable() const noexcept;
    const uint16_t GetAllocationMgr() const noexcept;
    const std::size_t GetNumDescriptors() const noexcept;

    const D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(const UINT& offset) const noexcept;
    const D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(const UINT& offset) const noexcept;
};

class IDescriptorAllocator
{
   public:
    NODISCARD virtual DescriptorHeapAllocation Allocate(const std::size_t& count) = 0;
    virtual void Free(DescriptorHeapAllocation&& allocation) = 0;
    NODISCARD virtual const uint16_t GetDescirptorIncSize() const = 0;
};

class DescriptorHeapAllocationMgr final
{
    Engine::VariableSizeAllocationsManager block_alloc_mgr;
    IDescriptorAllocator& allocator;
    ComPtr<ID3D12DescriptorHeap> descriptor_heap;
    D3D12_CPU_DESCRIPTOR_HANDLE cpu_base_address;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_base_address;
    D3D12_DESCRIPTOR_HEAP_DESC heap_desc;
    uint16_t mgr_id;

   public:
    DescriptorHeapAllocationMgr(IDescriptorAllocator& _allocator,
                                IAllocator& mem_allocator,
                                RenderDeviceD3D12& device,
                                D3D12_DESCRIPTOR_HEAP_DESC heap_desc,
                                const uint16_t& mgr_id) noexcept;

    DescriptorHeapAllocationMgr(IDescriptorAllocator& _allocator,
                                IAllocator& mem_allocator,
                                ID3D12DescriptorHeap* p_descriptor_heap,
                                const uint16_t& mgr_id,
                                const std::size_t& offset,
                                const std::size_t& num_descriptors) noexcept;

    NODISCARD DescriptorHeapAllocation Allocate(const std::size_t& count);
    void Free(DescriptorHeapAllocation&& allocation);
    NODISCARD const std::size_t GetMaxDescriptors() const noexcept;
    NODISCARD const std::size_t GetAvailableDescriptors() const noexcept;
    NODISCARD const uint16_t GetMgrId() const noexcept;

   private:
};

class DecriptorSuballocationMgr final
{
    DescriptorHeapAllocationMgr alloc_mgr;
    std::vector<DescriptorHeapAllocation> chunk_allocations;
    std::size_t chunk_size;
    std::size_t current_chunk_offset = 0;
    IDescriptorAllocator& allocator;

   public:
    DecriptorSuballocationMgr(IDescriptorAllocator& allocator,
                              IAllocator& mem_allocator,
                              ID3D12DescriptorHeap* p_descriptor_heap,
                              const uint16_t& mgr_id,
                              const std::size_t& offset,
                              const std::size_t& num_descriptors,
                              const std::size_t& dynamic_chunk_size) noexcept;

    NODISCARD DescriptorHeapAllocation Allocate(const std::size_t& count);
    void Free(DescriptorHeapAllocation&& allocation);
    NODISCARD const std::size_t GetMaxDescriptors() const noexcept;
    NODISCARD const std::size_t GetAvailableDescriptors() const noexcept;
};

class CPUDescriptorHeap final : public IDescriptorAllocator
{
    std::vector<DescriptorHeapAllocationMgr> alloc_mgrs;
    D3D12_DESCRIPTOR_HEAP_DESC heap_desc;
    uint16_t descriptor_size;
    RenderDeviceD3D12& device_d3d12;
    IAllocator& mem_allocator;
    std::mutex alloc_mutex;

   public:
    CPUDescriptorHeap(IAllocator& _mem_allocator,
                      RenderDeviceD3D12& device,
                      const D3D12_DESCRIPTOR_HEAP_TYPE& heap_type,
                      const std::size_t& num_descriptors);
    ~CPUDescriptorHeap();

    NODISCARD virtual DescriptorHeapAllocation Allocate(const std::size_t& count) override;
    virtual void Free(DescriptorHeapAllocation&& allocation) override;
    NODISCARD virtual const uint16_t GetDescirptorIncSize() const noexcept override;

    NODISCARD const std::size_t GetMaxDescriptors() const noexcept;
    NODISCARD const std::size_t GetAvailableDescriptors() const noexcept;

   private:
    void FreeAllocation(DescriptorHeapAllocation&& allocation);
};

class GPUDescriptorHeap final : public IDescriptorAllocator
{
    D3D12_DESCRIPTOR_HEAP_DESC heap_desc;
    ComPtr<ID3D12DescriptorHeap> descriptor_heap;
    uint16_t descriptor_size;
    RenderDeviceD3D12& device_d3d12;
    IAllocator& mem_allocator;
    std::mutex static_alloc_mutex;
    std::mutex dynamic_alloc_mutex;

    DescriptorHeapAllocationMgr static_alloc_mgr;
    DecriptorSuballocationMgr dynamic_alloc_mgr;

   public:
    GPUDescriptorHeap(IAllocator& _mem_allocator,
                      RenderDeviceD3D12& device,
                      const D3D12_DESCRIPTOR_HEAP_TYPE& heap_type,
                      const std::size_t& num_static_descriptors,
                      const std::size_t& num_dynamic_descriptors,
                      const std::size_t& dynamic_chunk_size) noexcept;
    ~GPUDescriptorHeap();
    NODISCARD virtual DescriptorHeapAllocation Allocate(const std::size_t& count) override;  // alloc static
    NODISCARD DescriptorHeapAllocation AllocateDynamic(const std::size_t& count);            // alloc dynamic
    virtual void Free(DescriptorHeapAllocation&& allocation) override;
    NODISCARD virtual const uint16_t GetDescirptorIncSize() const noexcept override;
    void FreeAllocations();
    NODISCARD const std::size_t GetMaxStaticDescriptors() const noexcept;
    NODISCARD const std::size_t GetMaxDynamicDescriptors() const noexcept;
    NODISCARD const std::size_t GetStaticAvailableDescriptors() const noexcept;
    NODISCARD const std::size_t GetDynamicAvailableDescriptors() const noexcept;

   private:
    void FreeAllocation(DescriptorHeapAllocation&& allocation);
};

}  // namespace Toy::Graphics