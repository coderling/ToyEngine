#pragma once
#include "IObject.hpp"

namespace Toy::Engine::Rendering
{
class IMesh : public IObject
{
   public:
    INTERFACEUUID(IMesh) = {/* 1f46ec08-1a2e-46f7-b70e-ccea0ba214ed */
                            0x1f46ec08,
                            0x1a2e,
                            0x46f7,
                            {0xb7, 0x0e, 0xcc, 0xea, 0x0b, 0xa2, 0x14, 0xed}};
};
}  // namespace Toy::Engine::Rendering