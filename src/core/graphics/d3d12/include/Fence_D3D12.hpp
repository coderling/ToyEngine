#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IFence.hpp>

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class Fence final : public IFence
{
    ComPtr<ID3D12Fence> fence;
    HANDLE fence_event;

   public:
    Fence(const uint64_t& init_va, const D3D12_FENCE_FLAGS& flag, HANDLE fence_event);
    uint64_t GetCompletedValue() const override;
    // cpu side signal
    void Signal(uint64_t fence_value) override;
    void Wait(uint64_t fence_value) override;
    ID3D12Fence* GetFence() const noexcept;

   private:
    Fence() = default;
    void OnDestroy() override;
};
}  // namespace Toy::Graphics