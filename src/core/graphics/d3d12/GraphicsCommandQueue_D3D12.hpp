#pragma once
#include <wrl.h>

#include "IGraphicsCommandQueue.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class GraphicsCommandQueue final : public IGraphicsCommandQueue
{
   public:
    IDeviceCommandQueue* GetDeviceQueue() const noexcept { return common_queue.Get(); }
    void ExecuteCommandList(const IGraphicsCommandList* cmd_list);
    void ExecuteCommandListSync(const IGraphicsCommandList* cmd_list);
    void ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const* cmd_list);
    void ExecuteCommandListsSync(const std::size_t& num, const IGraphicsCommandList* const* cmd_lists);
    void Signal(ID3D12Fence* fence, const std::uint64_t& fence_value);

    GraphicsCommandQueue(const COMMAND_QUEUE_DESC* desc);
    GraphicsCommandQueue() = delete;

   protected:
    void OnDestroy() override;

   private:
    ComPtr<IDeviceCommandQueue> common_queue;
};
}  // namespace Toy::Graphics
