#pragma once
#include <wrl.h>

#include "ICommandQueueD3D12.hpp"
#include "TObject.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class CommandQueueD3D12 final : public Toy::Engine::TObject<ICommandQueueD3D12>
{
    using TBase = Toy::Engine::TObject<ICommandQueueD3D12>;
    ComPtr<ID3D12CommandQueue> p_common_queue;
    ComPtr<ID3D12Fence> p_fence;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(CommandQueueD3D12, ID3D12CommandQueue* _p_command_queue, ID3D12Fence* _p_fence);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    uint64_t GetCompletedFenceValue() const noexcept override;
    uint64_t GetNextFenceValue() const noexcept override;
    uint64_t WaitForGpu() override;

    ID3D12CommandQueue* GetDeviceQueue() const noexcept override;
    void ExecuteCommandList(const ID3D12DebugCommandList* cmd_list) override;
    void ExecuteCommandListSync(const ID3D12DebugCommandList* cmd_list) override;
    void ExecuteCommandLists(const std::size_t& num, const ID3D12DebugCommandList* const* cmd_list) override;
    void ExecuteCommandListsSync(const std::size_t& num, const ID3D12DebugCommandList* const* cmd_lists) override;
    void Signal(ID3D12Fence* fence, const std::uint64_t& fence_value) override;
    void WailFence(ID3D12Fence* fence, const std::uint64_t& fence_value) override;

   private:
    void OnDestroy() override;
};
}  // namespace Toy::Graphics
