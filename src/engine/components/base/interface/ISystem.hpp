#pragma once

#include "SystemMgr.hpp"
#include "TObject.hpp"
#include "IRunTimeModule.hpp"

namespace Toy::Engine
{
class ISystem : public IObject, IRunTimeModule
{
   public:
   protected:
    void OnDestroy() override final { Finalize(); }

    virtual void Finalize() override = 0;
};

}  // namespace Toy::Engine