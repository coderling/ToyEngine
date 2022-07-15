#pragma once
#include "IObject.hpp"

namespace Toy::Engine
{
class ICamera : public IObject
{
   public:
    INTERFACEUUID(ICamera) = {/* 6098d06e-7372-41ba-80aa-e045748fe8da */
                              0x6098d06e,
                              0x7372,
                              0x41ba,
                              {0x80, 0xaa, 0xe0, 0x45, 0x74, 0x8f, 0xe8, 0xda}};
};
}  // namespace Toy::Engine