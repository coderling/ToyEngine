#pragma once

#include <wrl.h>
#include <memory>
#include <vector>
#include "Fence_D3D12.hpp"
#include "GraphicsCommandQueue_D3D12.hpp"
#include "IGraphics.hpp"
#include "SwapChain_D3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class Graphics final : public IGraphics
{
   public:
    int Initialize() override;

    IDevice* GetDevice() const noexcept override { return device.Get(); }
    ISwapChain* GetSwapChain() const noexcept override { return swapchain.get(); }
    IGraphicsCommandQueue* GetCommandQueue() const noexcept override { return command_queue.get(); }
    void WaitForGpu() override;
    void FinishFrame() override;

   protected:
    void Finalize() override;

   private:
    ComPtr<IDevice> device;
    std::unique_ptr<SwapChain> swapchain;
    std::unique_ptr<GraphicsCommandQueue> command_queue;
    ComPtr<IDeviceCommandAllocator> common_allocator;

    // synchronization
    UINT frame_index = 0;
    std::unique_ptr<Fence> fence;
    std::vector<UINT64> fence_values;
};
}  // namespace Toy::Graphics
