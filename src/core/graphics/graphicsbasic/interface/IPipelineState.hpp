#pragma once
#include "IObject.hpp"

namespace Toy::Graphics
{
class IPipelineState : public IObject
{
   public:
    INTERFACEUUID(IPipelineState) = {/* 17d892f1-2eaa-4aac-b5e4-3ed43829b8f6 */
                                     0x17d892f1,
                                     0x2eaa,
                                     0x4aac,
                                     {0xb5, 0xe4, 0x3e, 0xd4, 0x38, 0x29, 0xb8, 0xf6}};
};
}  // namespace Toy::Graphics