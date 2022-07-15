#pragma once
#include "IObject.hpp"

namespace Toy::Engine::Rendering
{
class IMaterial : public Toy::IObject
{
   public:
    INTERFACEUUID(IMaterial) = {/* 35dc928e-104c-4232-984e-84b1b1e8905c */
                                0x35dc928e,
                                0x104c,
                                0x4232,
                                {0x98, 0x4e, 0x84, 0xb1, 0xb1, 0xe8, 0x90, 0x5c}};
};
}  // namespace Toy::Engine::Rendering