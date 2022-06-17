#pragma once

#include <memory>
#include "AppArgs.hpp"

namespace Toy::Graphics
{
class IGraphics;
class IPipeline;
}  // namespace Toy::Graphics

namespace Toy::Platform
{
class EngineLoop;
}

namespace Toy::Engine
{
struct GlobalEnvironment
{
   public:
    Toy::Graphics::IGraphics* GetGraphics() const noexcept { return graphics; }
    Toy::Graphics::IPipeline* GetPipeline() const noexcept { return pipeline; }
    const AppArgs* GetArgs() const noexcept { return init_args; }
    static GlobalEnvironment& GetEnv();

   private:
    friend class SystemMgr;
    friend class Platform::EngineLoop;
    Toy::Graphics::IGraphics* graphics = nullptr;
    Toy::Graphics::IPipeline* pipeline = nullptr;
    const AppArgs* init_args = nullptr;
};

}  // namespace Toy::Engine
