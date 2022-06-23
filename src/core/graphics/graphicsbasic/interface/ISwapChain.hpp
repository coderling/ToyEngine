#pragma once

#include "IObject.hpp"

#include <cstdint>

namespace Toy::Graphics
{
class ISwapChain : public IObject
{
   public:
    static constexpr const IUUID CLS_UUID = {/* 1aa81092-0a34-46cb-96c3-a3fb7bed09c2 */
                                             0x1aa81092,
                                             0x0a34,
                                             0x46cb,
                                             {0x96, 0xc3, 0xa3, 0xfb, 0x7b, 0xed, 0x09, 0xc2}};

    virtual void Present() = 0;
    virtual void Resize(uint32_t width, uint32_t height) = 0;
    virtual bool IsFullScreen() const noexcept = 0;
    virtual void SetFullScreen(bool state) = 0;
    virtual uint32_t GetCurrentBackBufferIndex() = 0;
};
}  // namespace Toy::Graphics