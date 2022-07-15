#pragma once
#include "IPipelineState.hpp"

namespace Toy::Graphics
{
class IPipelineStateD3D12 : public IPipelineState
{
   public:
    INTERFACEUUID(IPipelineStateD3D12) = {/* b8a4a7df-781e-45a3-a01c-8ab7e224768c */
                                          0xb8a4a7df,
                                          0x781e,
                                          0x45a3,
                                          {0xa0, 0x1c, 0x8a, 0xb7, 0xe2, 0x24, 0x76, 0x8c}};
};
}  // namespace Toy::Graphics