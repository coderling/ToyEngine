#pragma once

#include <wrl.h>
#include <memory>
#include <vector>
#include "DescriptorHeap.hpp"
#include "EngineSetting.hpp"
#include "FenceD3D12.hpp"
#include "GraphicsCommandQueueD3D12.hpp"
#include "RefCountPtr.hpp"
#include "RenderDeviceBase.hpp"
#include "SwapChainD3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class RenderDeviceD3D12 final : public RenderDeviceBase<IRenderDevice>
{
    using TBase = RenderDeviceBase<IRenderDevice>;
    ComPtr<IDevice> device;
    RefCountPtr<SwapChain> swapchain;
    RefCountPtr<GraphicsCommandQueueD3D12> command_queue;
    ComPtr<IDeviceCommandAllocator> common_allocator;

    // synchronization
    UINT frame_index = 0;
    RefCountPtr<FenceD3D12> p_fence;
    std::vector<UINT64> fence_values;

    // 0: D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
    // 1: D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
    // 2: D3D12_DESCRIPTOR_HEAP_TYPE_RTV
    //  3:D3D12_DESCRIPTOR_HEAP_TYPE_DSV
    CPUDescriptorHeap cpu_descriptorheap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
    // 0: D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
    // 1: D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
    GPUDescriptorHeap gpu_descriptorheap[2];

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    int Initialize() override;

    IDevice* GetDevice() const noexcept override { return device.Get(); }
    ISwapChain* GetSwapChain() const noexcept override { return swapchain.RawPtr(); }
    IGraphicsCommandQueue* GetCommandQueue() const noexcept override { return command_queue.RawPtr(); }
    void WaitForGpu() override;
    void FinishFrame() override;
    template <typename ObjectType, typename = typename std::enable_if<std::is_object<ObjectType>::value>::type>
    void SafeReleaseGPUObject(ObjectType&& object)
    {
    }

   protected:
    void OnDestroy() override;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(RenderDeviceD3D12, const EngineSetting& setting);
};
}  // namespace Toy::Graphics
