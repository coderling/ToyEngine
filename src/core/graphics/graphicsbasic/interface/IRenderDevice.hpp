#pragma once

#include "GraphicsDef.hpp"
#include "IGraphicsCommandQueue.hpp"
#include "IObject.hpp"
#include "ISwapChain.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
class IRenderDevice : public IObject
{
   public:
    INTERFACEUUID(IRenderDevice) = {/* e392bb95-1463-4387-b111-6e0338cf7677 */
                                    0xe392bb95,
                                    0x1463,
                                    0x4387,
                                    {0xb1, 0x11, 0x6e, 0x03, 0x38, 0xcf, 0x76, 0x77}};
    static IRenderDevice* GetInstance();
    virtual int Initialize() = 0;
    virtual IDevice* GetDevice() const noexcept = 0;
    virtual ISwapChain* GetSwapChain() const noexcept = 0;
    virtual IGraphicsCommandQueue* GetCommandQueue() const noexcept = 0;
    virtual void WaitForGpu() = 0;
    virtual void FinishFrame() = 0;

   protected:
   protected:
};
}  // namespace Toy::Graphics