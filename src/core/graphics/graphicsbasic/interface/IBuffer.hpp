#pragma once
#include "IObject.hpp"

namespace Toy::Graphics
{
class IBuffer : public IObject
{
   public:
    INTERFACEUUID(IRenderDevice) = {/* e0c9332d-ede9-479e-aaa7-b44ba679ca38 */
                                    0xe0c9332d,
                                    0xede9,
                                    0x479e,
                                    {0xaa, 0xa7, 0xb4, 0x4b, 0xa6, 0x79, 0xca, 0x38}};
};
}  // namespace Toy::Graphics