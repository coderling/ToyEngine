#pragma once

#include <cstdint>
#include <string>
#include "AppArgs.hpp"
#include "CommonDefines.hpp"
#include "ISystem.hpp"

namespace Toy::Engine
{
struct GlobalEnvironment;

class IClient : IRunTimeModule
{
   public:
    NODISCARD virtual void* GetHwnd() const noexcept = 0;
    NODISCARD virtual const AppArgs& GetArgs() const noexcept = 0;
    NODISCARD virtual bool IsQuit() const noexcept = 0;
    virtual void Quit() = 0;

   protected:
    virtual int CreateAppWindow() = 0;
};
}  // namespace Toy::Engine