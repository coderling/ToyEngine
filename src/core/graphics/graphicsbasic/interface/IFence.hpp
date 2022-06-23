#pragma once
#include <stdint.h>
#include <IObject.hpp>

namespace Toy::Graphics
{
class IFence : public IObject
{
   public:
    static constexpr const IUUID CLS_UUID = {/* ed5f88bb-8444-4042-a6bd-36cdb23701c0 */
                                             0xed5f88bb,
                                             0x8444,
                                             0x4042,
                                             {0xa6, 0xbd, 0x36, 0xcd, 0xb2, 0x37, 0x01, 0xc0}};

    virtual uint64_t GetCompletedValue() const = 0;
    virtual void Signal(uint64_t fence_value) = 0;
    virtual void Wait(uint64_t fence_value) = 0;
};
}  // namespace Toy::Graphics