#pragma once
#include "IDeviceContext.hpp"
namespace Toy::Graphics
{
class IDeviceContextD3D12 : public IDeviceContext
{
   public:
    INTERFACEUUID(IDeviceContextD3D12) = {/* b1e2763f-4a05-4d83-b6cf-8d3f74df3ffc */
                                          0xb1e2763f,
                                          0x4a05,
                                          0x4d83,
                                          {0xb6, 0xcf, 0x8d, 0x3f, 0x74, 0xdf, 0x3f, 0xfc}};

    
};
}  // namespace Toy::Graphics