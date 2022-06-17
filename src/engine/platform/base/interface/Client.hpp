#pragma once

#include <cstdint>
#include <string>
#include "AppArgs.hpp"
#include "CommonDefines.hpp"
#include "ISystem.hpp"

namespace Toy::Engine
{
struct GlobalEnvironment;

class IClient : public ISystem
{
   public:
    int Initialize() override = 0;
    void Tick() override = 0;

    NODISCARD virtual void* GetHwnd() const noexcept = 0;
    NODISCARD virtual const AppArgs& GetArgs() const noexcept = 0;
    NODISCARD virtual bool IsQuit() const noexcept = 0;
    virtual void Quit() = 0;

   protected:
    void Finalize() override = 0;
    virtual int CreateAppWindow() = 0;
};
}  // namespace Toy::Engine