#include "FenceD3D12.hpp"
#include <DebugUtility.hpp>
#include <GlobalEnvironment.hpp>
#include <IRenderDevice.hpp>
#include "Utility.hpp"

namespace Toy::Graphics
{

IMPLEMENT_CONSTRUCT_DEFINE_HEAD(TBase, FenceD3D12, const uint64_t& init_va, const D3D12_FENCE_FLAGS& flag, HANDLE fence_event)
{
    auto graphics = GlobalEnvironment::GetEnv().GetGraphics();
    ENGINE_DEV_CHECK_EXPR(graphics != nullptr, "graphics is nullptr!");
    auto device = graphics->GetDevice();
    ENGINE_DEV_CHECK_EXPR(device != nullptr, "device is nullptr!");
    ASSERT_SUCCEEDED(device->CreateFence(init_va, flag, MY_IID_PPV_ARGS(&fence)));
    this->fence_event = fence_event;
}

IMPLEMENT_QUERYINTERFACE(FenceD3D12, TBase)

void FenceD3D12::OnDestroy() { CloseHandle(fence_event); }

uint64_t FenceD3D12::GetCompletedValue() const
{
    uint64_t va = fence->GetCompletedValue();
    ENGINE_ASSERT_EXPR(va != UINT64_MAX, "device has be remove, fence return completed value as UINT64_MAX");
    return va;
}

void FenceD3D12::Signal(uint64_t fence_value) { fence->Signal(fence_value); }

void FenceD3D12::Wait(uint64_t fence_value)
{
    ENGINE_ASSERT_EXPR(fence_event != nullptr);
    if (GetCompletedValue() >= fence_value)
        {
            return;
        }

    ASSERT_SUCCEEDED(fence->SetEventOnCompletion(fence_value, fence_event));
    WaitForSingleObject(fence_event, INFINITE);
}

ID3D12Fence* FenceD3D12::GetFence() const noexcept { return fence.Get(); }

}  // namespace Toy::Graphics