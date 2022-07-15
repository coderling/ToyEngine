#pragma once
#include "ICommandQueue.hpp"

namespace Toy::Graphics
{
class ICommandQueueD3D12 : public ICommandQueue
{
   public:
    INTERFACEUUID(ICommandQueueD3D12) = {/* c020cbb2-bfdd-4aec-9b3f-cf93b0f6ffec */
                                         0xc020cbb2,
                                         0xbfdd,
                                         0x4aec,
                                         {0x9b, 0x3f, 0xcf, 0x93, 0xb0, 0xf6, 0xff, 0xec}};

    virtual ID3D12CommandQueue* GetDeviceQueue() const noexcept = 0;
    virtual void ExecuteCommandList(const ID3D12DebugCommandList* cmd_list) = 0;
    virtual void ExecuteCommandListSync(const ID3D12DebugCommandList* cmd_list) = 0;
    virtual void ExecuteCommandLists(const std::size_t& num, const ID3D12DebugCommandList* const* cmd_list) = 0;
    virtual void ExecuteCommandListsSync(const std::size_t& num, const ID3D12DebugCommandList* const* cmd_lists) = 0;
    virtual void Signal(ID3D12Fence* fence, const std::uint64_t& fence_value) = 0;
    virtual void WailFence(ID3D12Fence* fence, const std::uint64_t& fence_value) = 0;
};
}  // namespace Toy::Graphics