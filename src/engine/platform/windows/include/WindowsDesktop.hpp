#pragma once
#include "INativeWindow.hpp"
#include "TObject.hpp"
#include "EngineSetting.hpp"

namespace Toy::Platform
{
class WindowsDesktop final : Toy::Engine::TObject<INativeWindow>
{
    using TBase = Toy::Engine::TObject<INativeWindow>;
    IMPLEMENT_CONSTRUCT_STATEMENT(WindowsDesktop, const Engine::EngineSetting& seting, const char* title);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    void* GetHwnd() const noexcept override;

   protected:
    void OnDestroy() override;
};
}  // namespace Toy::Platform