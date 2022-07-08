#include "DescriptorHeap.hpp"
#include <mutex>
#include "GraphicsDef.hpp"
#include "RenderDeviceD3D12.hpp"

namespace Toy::Graphics
{
//------------------------------------------DescriptorHeapAllocation------------------------------//
DescriptorHeapAllocation::DescriptorHeapAllocation() noexcept
    : cpu_base_address{0},
      gpu_base_address{0},
      count{0},
      block_offset{Engine::VariableSizeAllocationsManager::OffsetSizeType(-1)},
      allocation_mgr{InvalidMgrId},
      inc_size{0},
      allocator{nullptr}
{
}

DescriptorHeapAllocation::DescriptorHeapAllocation(IDescriptorAllocator& _allocator,
                                                   const uint16_t& mgr_id,
                                                   const std::size_t& _count,
                                                   const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle,
                                                   const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle) noexcept
    : cpu_base_address{cpu_handle},
      gpu_base_address{gpu_handle},
      count{_count},
      block_offset{0},
      allocation_mgr{mgr_id},
      inc_size{_allocator.GetDescirptorIncSize()},
      allocator{&_allocator}
{
}

DescriptorHeapAllocation::~DescriptorHeapAllocation() noexcept
{
    if (!IsNull())
        {
            allocator->Free(std::move(*this));
        }
    ENGINE_ASSERT_EXPR(IsNull(), "Fail Destroy DescriptorHeapAllocation!!!");
}

void DescriptorHeapAllocation::Clear()
{
    cpu_base_address.ptr = 0;
    gpu_base_address.ptr = 0;
    count = 0;
    block_offset = 0;
    allocation_mgr = InvalidMgrId;
}

bool DescriptorHeapAllocation::IsNull() const noexcept { return cpu_base_address.ptr == 0; }

bool DescriptorHeapAllocation::IsShaderVisiable() const noexcept { return gpu_base_address.ptr != 0; }

const uint16_t DescriptorHeapAllocation::GetAllocationMgr() const noexcept { return allocation_mgr; }

const std::size_t DescriptorHeapAllocation::GetNumDescriptors() const noexcept { return count; }

const D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeapAllocation::GetCPUHandle(const UINT& offset) const noexcept
{
    ENGINE_ASSERT_EXPR(offset >= 0 && offset < count);
    auto cpu_ptr = cpu_base_address;
    cpu_ptr.ptr = static_cast<SIZE_T>(cpu_base_address.ptr + UINT64(offset) * UINT64(inc_size));
    return cpu_ptr;
}

const D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeapAllocation::GetGPUHandle(const UINT& offset) const noexcept
{
    ENGINE_ASSERT_EXPR(offset >= 0 && offset < count);
    if (!IsShaderVisiable())
        {
            return gpu_base_address;
        }

    auto gpu_ptr = gpu_base_address;
    gpu_ptr.ptr = static_cast<SIZE_T>(gpu_base_address.ptr + UINT64(offset) * UINT64(inc_size));
    return gpu_ptr;
}
//------------------------------------------End::DescriptorHeapAllocation------------------------------//

//------------------------------------------DescriptorHeapAllocationMgr ------------------------------//
DescriptorHeapAllocationMgr::DescriptorHeapAllocationMgr(IDescriptorAllocator& _allocator,
                                                         IAllocator& mem_allocator,
                                                         RenderDeviceD3D12& device,
                                                         D3D12_DESCRIPTOR_HEAP_DESC heap_desc,
                                                         const uint16_t& mgr_id) noexcept
    : DescriptorHeapAllocationMgr{_allocator,
                                  mem_allocator,
                                  [&] {
                                      ComPtr<ID3D12DescriptorHeap> heap;
                                      device.GetDevice()->CreateDescriptorHeap(&heap_desc, MY_IID_PPV_ARGS(&heap));
                                      auto raw_pheap = heap.Detach();
                                      return raw_pheap;
                                  }(),
                                  mgr_id,
                                  0,
                                  heap_desc.NumDescriptors}
{
}

DescriptorHeapAllocationMgr::DescriptorHeapAllocationMgr(IDescriptorAllocator& _allocator,
                                                         IAllocator& mem_allocator,
                                                         ID3D12DescriptorHeap* p_descriptor_heap,
                                                         const uint16_t& _mgr_id,
                                                         const std::size_t& offset,
                                                         const std::size_t& num_descriptors) noexcept
    : block_alloc_mgr(num_descriptors, mem_allocator),
      allocator{_allocator},
      descriptor_heap{p_descriptor_heap},
      heap_desc{p_descriptor_heap->GetDesc()},
      mgr_id{_mgr_id}
{
    cpu_base_address = descriptor_heap->GetCPUDescriptorHandleForHeapStart();
    cpu_base_address.ptr = static_cast<SIZE_T>(cpu_base_address.ptr + UINT64(offset) * UINT64(allocator.GetDescirptorIncSize()));

    gpu_base_address.ptr = 0;
    if (heap_desc.Flags & D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE)
        {
            gpu_base_address = descriptor_heap->GetGPUDescriptorHandleForHeapStart();
            gpu_base_address.ptr = static_cast<SIZE_T>(gpu_base_address.ptr + UINT64(offset) * UINT64(allocator.GetDescirptorIncSize()));
        }
}

DescriptorHeapAllocation DescriptorHeapAllocationMgr::Allocate(const std::size_t& count)
{
    auto block_alloc = block_alloc_mgr.Allocate(count, 1);
    if (!block_alloc.IsValid())
        {
            return DescriptorHeapAllocation{};
        }

    ENGINE_ASSERT_EXPR(count == block_alloc.size);

    auto cpu_ptr = D3D12_CPU_DESCRIPTOR_HANDLE{0};
    cpu_ptr.ptr = static_cast<SIZE_T>(cpu_base_address.ptr + UINT64(block_alloc.address_offset) * UINT64(allocator.GetDescirptorIncSize()));

    auto gpu_ptr = D3D12_GPU_DESCRIPTOR_HANDLE{0};
    if (heap_desc.Flags & D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE)
        {
            gpu_base_address = descriptor_heap->GetGPUDescriptorHandleForHeapStart();
            gpu_base_address.ptr =
                static_cast<SIZE_T>(gpu_base_address.ptr + UINT64(block_alloc.address_offset) * UINT64(allocator.GetDescirptorIncSize()));
        }

    auto allocation = DescriptorHeapAllocation(allocator, mgr_id, count, cpu_ptr, gpu_ptr);
    allocation.block_offset = block_alloc.address_offset;
    return allocation;
}

void DescriptorHeapAllocationMgr::Free(DescriptorHeapAllocation&& allocation)
{
    ENGINE_ASSERT_EXPR(allocation.GetAllocationMgr() == mgr_id, "not allocation by this mgr!!!");
    if (allocation.IsNull())
        {
            return;
        }

    block_alloc_mgr.Free(allocation.block_offset, allocation.GetNumDescriptors());

    allocation.Clear();
}

const std::size_t DescriptorHeapAllocationMgr::GetMaxDescriptors() const noexcept { return block_alloc_mgr.MaxSize(); }

const std::size_t DescriptorHeapAllocationMgr::GetAvailableDescriptors() const noexcept { return block_alloc_mgr.FreeSize(); }

const uint16_t DescriptorHeapAllocationMgr::GetMgrId() const noexcept { return mgr_id; }

//------------------------------------------End::DescriptorHeapAllocationMgr ------------------------------//

//--------------------------------------------DecriptorSuballocationMgr----------------------------//
DecriptorSuballocationMgr::DecriptorSuballocationMgr(IDescriptorAllocator& _allocator,
                                                     IAllocator& mem_allocator,
                                                     ID3D12DescriptorHeap* p_descriptor_heap,
                                                     const uint16_t& mgr_id,
                                                     const std::size_t& offset,
                                                     const std::size_t& num_descriptors,
                                                     const std::size_t& dynamic_chunk_size) noexcept
    : alloc_mgr{_allocator, mem_allocator, p_descriptor_heap, mgr_id, offset, num_descriptors},
      chunk_size{dynamic_chunk_size},
      current_chunk_offset{0},
      allocator{_allocator}
{
}

DescriptorHeapAllocation DecriptorSuballocationMgr::Allocate(const std::size_t& count)
{
    if (chunk_allocations.empty() || current_chunk_offset + count > chunk_allocations.back().GetNumDescriptors())
        {
            // new chunk
            std::size_t rcount = std::max(count, chunk_size);
            auto new_chunk = alloc_mgr.Allocate(count);
            chunk_allocations.emplace_back(std::move(new_chunk));
            current_chunk_offset = 0;
        }

    auto& chunk = chunk_allocations.back();
    DescriptorHeapAllocation allocation{allocator, alloc_mgr.GetMgrId(), count, chunk.GetCPUHandle(current_chunk_offset),
                                        chunk.GetGPUHandle(current_chunk_offset)};
    current_chunk_offset += count;

    return allocation;
}

void DecriptorSuballocationMgr::Free(DescriptorHeapAllocation&& allocation) { alloc_mgr.Free(std::move(allocation)); }

const std::size_t DecriptorSuballocationMgr::GetMaxDescriptors() const noexcept { return alloc_mgr.GetMaxDescriptors(); }

const std::size_t DecriptorSuballocationMgr::GetAvailableDescriptors() const noexcept { return alloc_mgr.GetAvailableDescriptors(); }

//--------------------------------------------End:DecriptorSuballocationMgr----------------------------//

//---------------------------------------------CPUDescriptorHeap---------------------------//

CPUDescriptorHeap::CPUDescriptorHeap(IAllocator& _mem_allocator,
                                     RenderDeviceD3D12& device,
                                     const D3D12_DESCRIPTOR_HEAP_TYPE& heap_type,
                                     const std::size_t& num_descriptors)
    : alloc_mgrs{},
      heap_desc{heap_type, static_cast<UINT>(num_descriptors), D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0 /*zero not support mulitple adapter*/},
      descriptor_size{static_cast<uint16_t>(device.GetDevice()->GetDescriptorHandleIncrementSize(heap_type))},
      device_d3d12{device},
      mem_allocator{_mem_allocator}
{
    alloc_mgrs.emplace_back(*this, mem_allocator, device, heap_desc, alloc_mgrs.size());
}

CPUDescriptorHeap::~CPUDescriptorHeap()
{
    std::size_t max = 0;
    std::size_t available = 0;
    for (auto& iter : alloc_mgrs)
        {
            max += iter.GetMaxDescriptors();
            available += iter.GetAvailableDescriptors();
        }

    ENGINE_DEV_CHECK_EXPR(max == available, "not all allocation release!!!");
}

DescriptorHeapAllocation CPUDescriptorHeap::Allocate(const std::size_t& count)
{
    std::lock_guard<std::mutex> lock_guard(alloc_mutex);

    DescriptorHeapAllocation alloc;
    for (auto& iter : alloc_mgrs)
        {
            alloc = iter.Allocate(count);
            if (!alloc.IsNull())
                {
                    break;
                }
        }

    if (alloc.IsNull())
        {
            if (count > heap_desc.NumDescriptors)
                {
                    LOG_WARNING("Allocate count(", count, ") exceeds the heap desc NumDescriptors(", heap_desc.NumDescriptors,
                                "). will increasing the num of heap!");
                }
            heap_desc.NumDescriptors = std::max(static_cast<UINT>(count), heap_desc.NumDescriptors);
            auto& mgr = alloc_mgrs.emplace_back(*this, mem_allocator, device_d3d12, heap_desc, alloc_mgrs.size());
            alloc = mgr.Allocate(count);
            ENGINE_ASSERT_EXPR(!alloc.IsNull());
        }

    return alloc;
}

void CPUDescriptorHeap::Free(DescriptorHeapAllocation&& allocation)
{
    struct ReleaseObjectHangle
    {
       private:
        CPUDescriptorHeap& heap;
        DescriptorHeapAllocation allocation;

       public:
        ReleaseObjectHangle(CPUDescriptorHeap& _heap, DescriptorHeapAllocation&& _allocation)
            : heap{_heap},
              allocation{std::move(_allocation)}
        {
        }

        NOCOPY_INPLACE(ReleaseObjectHangle);
        ReleaseObjectHangle& operator=(ReleaseObjectHangle&&) = delete;

        ~ReleaseObjectHangle() { heap.FreeAllocation(std::move(allocation)); }
    };

    device_d3d12.SafeReleaseGPUObject(ReleaseObjectHangle(*this, std::move(allocation)));
}

const uint16_t CPUDescriptorHeap::GetDescirptorIncSize() const noexcept { return descriptor_size; }

const std::size_t CPUDescriptorHeap::GetMaxDescriptors() const noexcept
{
    std::size_t count = 0;
    for (auto& iter : alloc_mgrs)
        {
            count += iter.GetMaxDescriptors();
        }

    return count;
}

const std::size_t CPUDescriptorHeap::GetAvailableDescriptors() const noexcept
{
    std::size_t count = 0;
    for (auto& iter : alloc_mgrs)
        {
            count += iter.GetAvailableDescriptors();
        }

    return count;
}

void CPUDescriptorHeap::FreeAllocation(DescriptorHeapAllocation&& allocation)
{
    std::lock_guard<std::mutex> lock_guard(alloc_mutex);
    auto mgr_index = allocation.GetAllocationMgr();
    ENGINE_ASSERT_EXPR(mgr_index >= 0 && mgr_index < alloc_mgrs.size());

    alloc_mgrs[mgr_index].Free(std::move(allocation));
}
//---------------------------------------------End::CPUDescriptorHeap---------------------------//

//---------------------------------------------GPUDescriptorHeap---------------------------//
GPUDescriptorHeap::GPUDescriptorHeap(IAllocator& _mem_allocator,
                                     RenderDeviceD3D12& device,
                                     const D3D12_DESCRIPTOR_HEAP_TYPE& heap_type,
                                     const std::size_t& num_static_descriptors,
                                     const std::size_t& num_dynamic_descriptors,
                                     const std::size_t& dynamic_chunk_size) noexcept
    : heap_desc{heap_type, static_cast<UINT>(num_static_descriptors + num_dynamic_descriptors), D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
                0 /*zero not support mulitple adapter*/},
      descriptor_heap{[&] {
          ComPtr<ID3D12DescriptorHeap> heap;
          device.GetDevice()->CreateDescriptorHeap(&heap_desc, MY_IID_PPV_ARGS(&heap));
          return heap;
      }()},
      descriptor_size{static_cast<uint16_t>(device.GetDevice()->GetDescriptorHandleIncrementSize(heap_type))},
      device_d3d12{device},
      mem_allocator{_mem_allocator},
      static_alloc_mgr{*this, mem_allocator, descriptor_heap.Get(), 0, 0, num_static_descriptors},
      dynamic_alloc_mgr{*this, mem_allocator, descriptor_heap.Get(), 1, num_static_descriptors, num_dynamic_descriptors, dynamic_chunk_size}
{
}

GPUDescriptorHeap::~GPUDescriptorHeap()
{
    ENGINE_DEV_CHECK_EXPR(static_alloc_mgr.GetMaxDescriptors() == static_alloc_mgr.GetAvailableDescriptors(),
                          "not all allocation release!!!");
    ENGINE_DEV_CHECK_EXPR(dynamic_alloc_mgr.GetMaxDescriptors() == dynamic_alloc_mgr.GetAvailableDescriptors(),
                          "not all allocation release!!!");
}

DescriptorHeapAllocation GPUDescriptorHeap::Allocate(const std::size_t& count)
{
    std::lock_guard<std::mutex> lock_guard(static_alloc_mutex);
    return static_alloc_mgr.Allocate(count);
}

DescriptorHeapAllocation GPUDescriptorHeap::AllocateDynamic(const std::size_t& count)
{
    std::lock_guard<std::mutex> lock_guard(dynamic_alloc_mutex);
    return dynamic_alloc_mgr.Allocate(count);
}

void GPUDescriptorHeap::Free(DescriptorHeapAllocation&& allocation)
{
    ENGINE_ASSERT_EXPR(allocation.GetAllocationMgr() == 0 || allocation.GetAllocationMgr() == 1);

    struct ReleaseObjectHangle
    {
       private:
        GPUDescriptorHeap& heap;
        DescriptorHeapAllocation allocation;

       public:
        ReleaseObjectHangle(GPUDescriptorHeap& _heap, DescriptorHeapAllocation&& _allocation)
            : heap{_heap},
              allocation{std::move(_allocation)}
        {
        }

        NOCOPY_INPLACE(ReleaseObjectHangle);
        ReleaseObjectHangle& operator=(ReleaseObjectHangle&&) = delete;

        ~ReleaseObjectHangle() { heap.FreeAllocation(std::move(allocation)); }
    };

    device_d3d12.SafeReleaseGPUObject(ReleaseObjectHangle(*this, std::move(allocation)));
}

void GPUDescriptorHeap::FreeAllocation(DescriptorHeapAllocation&& allocation)
{
    if (allocation.GetAllocationMgr() == 0)
        {
            std::lock_guard<std::mutex> lock_guard(static_alloc_mutex);
            static_alloc_mgr.Free(std::move(allocation));
        }
    else
        {
            std::lock_guard<std::mutex> lock_guard(dynamic_alloc_mutex);
            dynamic_alloc_mgr.Free(std::move(allocation));
        }
}

const uint16_t GPUDescriptorHeap::GetDescirptorIncSize() const noexcept { return descriptor_size; }

const std::size_t GPUDescriptorHeap::GetMaxStaticDescriptors() const noexcept { return static_alloc_mgr.GetMaxDescriptors(); }

const std::size_t GPUDescriptorHeap::GetStaticAvailableDescriptors() const noexcept { return static_alloc_mgr.GetAvailableDescriptors(); }

const std::size_t GPUDescriptorHeap::GetMaxDynamicDescriptors() const noexcept { return dynamic_alloc_mgr.GetMaxDescriptors(); }

const std::size_t GPUDescriptorHeap::GetDynamicAvailableDescriptors() const noexcept { return dynamic_alloc_mgr.GetAvailableDescriptors(); }

//---------------------------------------------End::GPUDescriptorHeap---------------------------//
}  // namespace Toy::Graphics