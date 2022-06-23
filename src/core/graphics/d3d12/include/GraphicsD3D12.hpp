#pragma once

#include <wrl.h>
#include <memory>
#include <vector>
#include "FenceD3D12.hpp"
#include "GraphicsCommandQueueD3D12.hpp"
#include "IGraphics.hpp"
#include "RefCountPtr.hpp"
#include "SwapChainD3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class GraphicsD3D12 final : TObject<IGraphics>
{
    using TBase = TObject<IGraphics>;
    ComPtr<IDevice> device;
    RefCountPtr<SwapChain> swapchain;
    RefCountPtr<GraphicsCommandQueueD3D12> command_queue;
    ComPtr<IDeviceCommandAllocator> common_allocator;

    // synchronization
    UINT frame_index = 0;
    RefCountPtr<FenceD3D12> p_fence;
    std::vector<UINT64> fence_values;

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    int Initialize() override;

    IDevice* GetDevice() const noexcept override { return device.Get(); }
    ISwapChain* GetSwapChain() const noexcept override { return swapchain.RawPtr(); }
    IGraphicsCommandQueue* GetCommandQueue() const noexcept override { return command_queue.RawPtr(); }
    void WaitForGpu() override;
    void FinishFrame() override;

   protected:
    void OnDestroy() override;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(GraphicsD3D12);
};
}  // namespace Toy::Graphics
