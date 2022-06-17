#pragma once

#include <memory>
#include "pch.hpp"

namespace Toy::Graphics
{
class IGraphics;
class IPipeline;
}  // namespace Toy::Graphics

namespace Toy::Engine
{
struct TOY_LIB_API GlobalEnvironment
{
   public:
    Toy::Graphics::IGraphics* GetGraphics() const noexcept { return graphics; }
    Toy::Graphics::IPipeline* GetPipeline() const noexcept { return pipeline; }
    static GlobalEnvironment& GetEnv();

   private:
    friend class SystemMgr;
    Toy::Graphics::IGraphics* graphics = nullptr;
    Toy::Graphics::IPipeline* pipeline = nullptr;
};

}  // namespace Toy::Engine
