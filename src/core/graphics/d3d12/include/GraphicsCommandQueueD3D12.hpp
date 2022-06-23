#pragma once
#include <wrl.h>

#include "IGraphicsCommandQueue.hpp"
#include "TObject.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class GraphicsCommandQueueD3D12 final : public Toy::Engine::TObject<IGraphicsCommandQueue>
{
    using TBase = Toy::Engine::TObject<IGraphicsCommandQueue>;
    ComPtr<IDeviceCommandQueue> common_queue;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(GraphicsCommandQueueD3D12, const COMMAND_QUEUE_DESC& desc);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    IDeviceCommandQueue* GetDeviceQueue() const noexcept { return common_queue.Get(); }
    void ExecuteCommandList(const IGraphicsCommandList* cmd_list);
    void ExecuteCommandListSync(const IGraphicsCommandList* cmd_list);
    void ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const* cmd_list);
    void ExecuteCommandListsSync(const std::size_t& num, const IGraphicsCommandList* const* cmd_lists);
    void Signal(ID3D12Fence* fence, const std::uint64_t& fence_value);

   protected:
    void OnDestroy() override;
};
}  // namespace Toy::Graphics
