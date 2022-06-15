#pragma once

#include <IGraphicsCommandList.hpp>
#include "IObject.hpp"


namespace Toy::Graphics
{
class IFrameResource : public Toy::Engine::IObject, public Toy::Engine::NoCopy
{
   public:
    virtual void Create() = 0;
    virtual IGraphicsCommandList* GetCommandList() = 0;
};
}  // namespace Toy::Graphics