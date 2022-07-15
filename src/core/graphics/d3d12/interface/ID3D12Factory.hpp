#pragma once
#include "EngineSetting.hpp"
#include "IDXCCompiler.hpp"
#include "IDeviceContext.hpp"
#include "IRenderDevice.hpp"
#include "ISwapChain.hpp"
#include "LoadDLL.hpp"

namespace Toy::Graphics
{
struct ID3D12Factory
{
   public:
    virtual void CreateDXCCompiler(IDXCCompiler** pp_compiler) = 0;
    virtual void CreateDeviceAndDeviceContext(const EngineSetting& setting, IRenderDevice** pp_device, IDeviceContext** pp_context) = 0;
    virtual void CreateSwapChain(
        const EngineSetting& setting, IRenderDevice* p_device, IDeviceContext* p_context, void* hwnd, ISwapChain** pp_swapchain) = 0;
    virtual void CreateCommandQueue(ID3D12Device* d3d12_device, ICommandQueue** pp_command_queue) = 0;
};

}  // namespace Toy::Graphics

#if ENGINE_DLL_EXPORT
typedef Toy::Graphics::ID3D12Factory* (*GetD3D12FactoryType)();
inline GetD3D12FactoryType LoadGraphicsD3D12()
{
    return (GetD3D12FactoryType)(Toy::Engine::LoadDLL("RenderDeviceD3D12", "GetD3D12Factory"));
}
#else
#endif
Toy::Graphics::ID3D12Factory* GetD3D12Factory();
