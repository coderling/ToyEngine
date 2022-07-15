#pragma once
#include "IObject.hpp"

namespace Toy::Platform
{
class INativeWindow : public IObject
{
   public:
    INTERFACEUUID(INativeWindow) = {/* 7ba22264-0c7e-425d-a91e-cd3287f4d356 */
                                    0x7ba22264,
                                    0x0c7e,
                                    0x425d,
                                    {0xa9, 0x1e, 0xcd, 0x32, 0x87, 0xf4, 0xd3, 0x56}};

    virtual void* GetHwnd() const noexcept = 0;
};
}  // namespace Toy::Platform