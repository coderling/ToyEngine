#pragma once

#include "ISwapChain.hpp"

namespace Toy::Graphics
{
class ISwapChainD3D12 : public ISwapChain
{
   public:
    INTERFACEUUID(ISwapChainD3D12) = {/* aab38899-c8f9-41e6-a1f6-e63725885123 */
                                      0xaab38899,
                                      0xc8f9,
                                      0x41e6,
                                      {0xa1, 0xf6, 0xe6, 0x37, 0x25, 0x88, 0x51, 0x23}};
};
}  // namespace Toy::Graphics