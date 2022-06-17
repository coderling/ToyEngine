#pragma once
#include <stdint.h>
#include <IObject.hpp>

namespace Toy::Graphics
{
class IFence : public Engine::IObject, public Engine::NoCopy
{
   public:
    virtual uint64_t GetCompletedValue() const = 0;
    virtual void Signal(uint64_t fence_value) = 0;
    virtual void Wait(uint64_t fence_value) = 0;
};
}  // namespace Toy::Graphics