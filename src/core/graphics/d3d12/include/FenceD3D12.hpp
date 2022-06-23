#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IFence.hpp>
#include <TObject.hpp>

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class FenceD3D12 final : public Engine::TObject<IFence>
{
   private:
    using TBase = Engine::TObject<IFence>;

    ComPtr<ID3D12Fence> fence;
    HANDLE fence_event;

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    uint64_t GetCompletedValue() const override;

    // cpu side signal
    void Signal(uint64_t fence_value) override;

    void Wait(uint64_t fence_value) override;

    void OnDestroy() override;

    ID3D12Fence* GetFence() const noexcept;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(FenceD3D12, const uint64_t& init_va, const D3D12_FENCE_FLAGS& flag, HANDLE fence_event);
};
}  // namespace Toy::Graphics