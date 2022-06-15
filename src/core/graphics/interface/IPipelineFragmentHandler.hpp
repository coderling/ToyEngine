#pragma once

#include "IObject.hpp"

namespace Toy::Graphics
{
class TOY_LIB_API IPipelineFragmentHandler : public Toy::Engine::IObject, public Toy::Engine::NoCopy
{
   public:
    virtual void Load() = 0;
    virtual void PreRender() = 0;
    virtual void Render() = 0;
    virtual void PostRender() = 0;
    virtual void Tick() = 0;
    virtual void Unload() = 0;
};

}  // namespace Toy::Graphics
