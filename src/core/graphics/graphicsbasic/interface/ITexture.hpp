#pragma once
#include "IObject.hpp"

namespace Toy::Graphics
{
class ITexture : public IObject
{
   public:
    INTERFACEUUID(ITexture) = {/* 9fc5ff74-6891-40a6-b583-6adf37ec7c7c */
                               0x9fc5ff74,
                               0x6891,
                               0x40a6,
                               {0xb5, 0x83, 0x6a, 0xdf, 0x37, 0xec, 0x7c, 0x7c}};
};
}  // namespace Toy::Graphics