#pragma once

#include "IObject.hpp"

namespace Toy::Engine
{
class TOY_LIB_API ISystem : public IObject, public NoCopy
{
   public:
    virtual int Initialize() = 0;
    virtual void Tick() = 0;

   protected:
    void OnDestroy() final override { Finalize(); }
    virtual void Finalize() = 0;
};
}  // namespace Toy::Engine