#include "Fence_D3D12.hpp"
#include <DebugUtility.hpp>
#include <GlobalEnvironment.hpp>
#include <IApp.hpp>
#include <IGraphics.hpp>
#include "Utility.hpp"

using namespace Toy::Graphics;

Fence::Fence(const uint64_t& init_va, const D3D12_FENCE_FLAGS& flag, HANDLE fence_event)
{
    auto graphics = Toy::Engine::IApp::env->GetGraphics();
    ENGINE_DEV_CHECK_EXPR(graphics != nullptr, "graphics is nullptr!");
    auto device = graphics->GetDevice();
    ENGINE_DEV_CHECK_EXPR(device != nullptr, "device is nullptr!");
    ASSERT_SUCCEEDED(device->CreateFence(init_va, flag, MY_IID_PPV_ARGS(&fence)));
    this->fence_event = fence_event;
}

void Fence::OnDestroy() { CloseHandle(fence_event); }

uint64_t Fence::GetCompletedValue() const
{
    uint64_t va = fence->GetCompletedValue();
    ENGINE_ASSERT_EXPR(va != UINT64_MAX, "device has be remove, fence return completed value as UINT64_MAX");
    return va;
}

void Fence::Signal(uint64_t fence_value) { fence->Signal(fence_value); }

void Fence::Wait(uint64_t fence_value)
{
    ENGINE_ASSERT_EXPR(fence_event != nullptr);
    if (GetCompletedValue() >= fence_value)
        {
            return;
        }

    ASSERT_SUCCEEDED(fence->SetEventOnCompletion(fence_value, fence_event));
    WaitForSingleObject(fence_event, INFINITE);
}

ID3D12Fence* Fence::GetFence() const noexcept { return fence.Get(); }