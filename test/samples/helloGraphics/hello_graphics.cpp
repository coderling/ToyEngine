#include "ID3D12Factory.hpp"
#include "RefCountPtr.hpp"
#include "IDXCCompiler.hpp"
#include "IDeviceContextD3D12.hpp"
#include "IRenderDeviceD3D12.hpp"
#include "IShader.hpp"
#include "CommandLineParse.hpp"
#include "Platform.hpp"

int main(int argc, char **argv)
{
    Toy::Graphics::ID3D12Factory *p_factory = nullptr;
#ifdef ENGINE_DLL_EXPORT
    auto get_factory_func = LoadGraphicsD3D12();
    p_factory = get_factory_func();
#else
    p_factory = GetD3D12Factory();
#endif
    Toy::Engine::EngineSetting setting;
    Toy::CommandLineParse::Parse(setting, argc, argv);

    Toy::Engine::RefCountPtr<Toy::Graphics::IRenderDevice> p_render_device;
    Toy::Engine::RefCountPtr<Toy::Graphics::IDeviceContext> p_device_context;
    Toy::Engine::RefCountPtr<Toy::Graphics::ISwapChain> p_swapchain;

    p_factory->CreateDeviceAndDeviceContext(setting, &p_render_device, &p_device_context);

    Toy::Engine::RefCountPtr<Toy::Platform::INativeWindow> p_nativewindow;
    Toy::Platform::CreateNativeWndow(&p_nativewindow);
    p_factory->CreateSwapChain(setting, p_render_device, p_device_context, p_nativewindow->GetHwnd(), &p_swapchain);

    Toy::Graphics::ShaderCreateInfo shader_vs_ci;
    shader_vs_ci.InitASCompileFromeSourceFile("assets/shaders/color.vs.cso");
    Toy::Engine::RefCountPtr<Toy::Graphics::IShader> p_vsshader;
    p_render_device->CreateShader(shader_vs_ci, &p_vsshader);

    Toy::Graphics::ShaderCreateInfo shader_ps_ci;
    shader_ps_ci.InitASCompileFromeSourceFile("assets/shaders/color.ps.cso");
    Toy::Engine::RefCountPtr<Toy::Graphics::IShader> p_psshader;
    p_render_device->CreateShader(shader_ps_ci, &p_psshader);

    return 0;
}