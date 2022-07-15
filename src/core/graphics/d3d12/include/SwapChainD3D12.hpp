#pragma once

#include <dxgi1_6.h>
#include <wrl.h>
#include "D3D12TypeTraits.hpp"
#include "IRenderDeviceD3D12.hpp"
#include "ISwapChainD3D12.hpp"
#include "SwapChainBase.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class SwapChainD3D12 final : public SwapChainBase<D3D12TypeTraits>
{
    using TBase = Toy::Engine::TObject<ISwapChain>;
    bool is_fullscreen;
    ComPtr<IDXGISwapChain3> swapchain = nullptr;

    IMPLEMENT_CONSTRUCT_STATEMENT(SwapChainD3D12, IRenderDeviceD3D12* _p_render_device, IDeviceContextD3D12* _p_device_context, void* hwnd);

   public:
    void Present() override;
    void Resize(uint32_t width, uint32_t height) override;
    void SetFullScreen(bool state) override;
    bool IsFullScreen() const noexcept override { return is_fullscreen; }
    uint32_t GetCurrentBackBufferIndex() override;

   protected:
    void OnDestroy() override;
};
}  // namespace Toy::Graphics