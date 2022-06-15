#pragma once

#include "GraphicsDef.hpp"
#include "IGraphicsCommandQueue.hpp"
#include "IObject.hpp"
#include "ISwapChain.hpp"


using namespace Toy::Engine;

namespace Toy::Graphics
{
class IGraphics : public IObject, public NoCopy
{
   public:
    static IGraphics* GetInstance();
    virtual int Initialize() = 0;
    virtual IDevice* GetDevice() const noexcept = 0;
    virtual ISwapChain* GetSwapChain() const noexcept = 0;
    virtual IGraphicsCommandQueue* GetCommandQueue() const noexcept = 0;
    virtual void WaitForGpu() = 0;
    virtual void FinishFrame() = 0;

   protected:
    void OnDestroy() final override { Finalize(); }

   protected:
    virtual void Finalize() = 0;
};
}  // namespace Toy::Graphics