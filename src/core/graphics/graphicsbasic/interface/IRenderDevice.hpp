#pragma once

#include "GraphicsDef.hpp"
#include "ICommandQueue.hpp"
#include "IObject.hpp"
#include "IPipelineState.hpp"
#include "IShader.hpp"
#include "ISwapChain.hpp"
#include "PipelineStateCreateInfo.hpp"

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
    virtual ICommandQueue* GetCommandQueue() const noexcept = 0;
    virtual void WaitForGpu() = 0;
    virtual void FinishFrame() = 0;
    virtual void CreatePipelineState(const PipelineStateCreateInfo& create_info, IPipelineState** pp_pipelinestate) = 0;
    virtual void CreateShader(const ShaderCreateInfo& create_info, IShader** pp_shader) = 0;

   protected:
};
}  // namespace Toy::Graphics