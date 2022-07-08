#pragma once

#include "SystemMgr.hpp"
#include "TObject.hpp"

namespace Toy::Engine
{
class ISystem : public IObject
{
   public:
    virtual int Initialize() = 0;
    virtual void Tick() = 0;

   protected:
    void OnDestroy() override final { Finalize(); }

    virtual void Finalize() = 0;
};

}  // namespace Toy::Engine