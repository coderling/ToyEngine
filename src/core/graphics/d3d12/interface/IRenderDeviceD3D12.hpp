#pragma once

#include "IRenderDevice.hpp"

namespace Toy::Graphics
{
class IRenderDeviceD3D12 : public IRenderDevice
{
   public:
    INTERFACEUUID(IRenderDeviceD3D12) = {/* fd61c814-7cc1-4548-983d-429d636d4375 */
                                         0xfd61c814,
                                         0x7cc1,
                                         0x4548,
                                         {0x98, 0x3d, 0x42, 0x9d, 0x63, 0x6d, 0x43, 0x75}};
};

}  // namespace Toy::Graphics