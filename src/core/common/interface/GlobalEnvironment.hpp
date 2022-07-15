#pragma once

#include <memory>
#include "AppArgs.hpp"

namespace Toy::Graphics
{
class IRenderDevice;
class IPipeline;
}  // namespace Toy::Graphics

namespace Toy::Platform
{
class Application;
}

namespace Toy::Engine
{
struct GlobalEnvironment
{
   public:
    Toy::Graphics::IRenderDevice* GetGraphics() const noexcept { return graphics; }
    Toy::Graphics::IPipeline* GetPipeline() const noexcept { return pipeline; }
    const AppArgs* GetArgs() const noexcept { return init_args; }
    void* GetHwnd() const noexcept { return hwnd; }
    static GlobalEnvironment& GetEnv();

   private:
    friend class SystemMgr;
    friend class Platform::Application;
    Toy::Graphics::IRenderDevice* graphics = nullptr;
    Toy::Graphics::IPipeline* pipeline = nullptr;
    const AppArgs* init_args = nullptr;
    void* hwnd = nullptr;
};

}  // namespace Toy::Engine
