#pragma once

#include "ISwapChain.hpp"

#include <dxgi1_6.h>
#include <wrl.h>
#include "TObject.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class SwapChain final : public Toy::Engine::TObject<ISwapChain>
{
    using TBase = Toy::Engine::TObject<ISwapChain>;
    bool is_fullscreen;
    ComPtr<IDXGISwapChain3> swapchain = nullptr;

    IMPLEMENT_CONSTRUCT_STATEMENT(SwapChain);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();
    int Initialize(IDXGIFactory* factory);
    void Present() override;
    void Resize(uint32_t width, uint32_t height) override;
    void SetFullScreen(bool state) override;
    bool IsFullScreen() const noexcept override { return is_fullscreen; }
    uint32_t GetCurrentBackBufferIndex() override;

   protected:
    void OnDestroy() override;
};
}  // namespace Toy::Graphics