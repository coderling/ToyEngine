#pragma once

#include <array>
#include <cstdint>
#include "GraphicsDef.hpp"
#include "IGraphicsCommandList.hpp"
#include "IObject.hpp"

namespace Toy::Graphics
{

class ICommandQueue : public IObject
{
   public:
    INTERFACEUUID(ICommandQueue) = {/* cb95f1fc-97e3-4ce2-a29c-efd5690b703b */
                                    0xcb95f1fc,
                                    0x97e3,
                                    0x4ce2,
                                    {0xa2, 0x9c, 0xef, 0xd5, 0x69, 0x0b, 0x70, 0x3b}};

    virtual uint64_t GetCompletedFenceValue() const noexcept = 0;
    virtual uint64_t GetNextFenceValue() const noexcept = 0;
    virtual uint64_t WaitForGpu() = 0;
};
}  // namespace Toy::Graphics
