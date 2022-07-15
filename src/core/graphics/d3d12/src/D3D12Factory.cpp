#include "CommandQueueD3D12.hpp"
#include "DXCCompiler.hpp"
#include "DefaultMemoryAllocator.hpp"
#include "DeviceContextD3D12.hpp"
#include "ID3D12Factory.hpp"
#include "ReferenceCounterObject.hpp"
#include "RenderDeviceD3D12.hpp"
#include "SwapChainD3D12.hpp"
#include "Utility.hpp"

namespace Toy::Graphics
{
class D3D12Factory final : public ID3D12Factory
{
   public:
    static D3D12Factory* GetInstance()
    {
        static D3D12Factory factory;
        return &factory;
    }

    void CreateDXCCompiler(IDXCCompiler** pp_compiler) override
    {
        auto raw_ptr = MAKE_REF_OBJECT(DXCCompiler, Engine::DefaultMemoryAllocator::GetGobalAllocator(), "DXCCompiler Instance")();
        raw_ptr->QueryInterface(IDXCCompiler::IDXCCompiler_UUID, reinterpret_cast<IObject**>(pp_compiler));
    }

    void CreateDeviceAndDeviceContext(const EngineSetting& setting, IRenderDevice** pp_device, IDeviceContext** pp_context) override
    {
        ComPtr<ID3D12Device> d3d12_device;
        UINT dxg_flactory_flags = 0;
#if defined(_DEBUG)
        ComPtr<ID3D12Debug> debug_controller;
        if (SUCCEEDED(D3D12GetDebugInterface(MY_IID_PPV_ARGS(&debug_controller))))
            {
                debug_controller->EnableDebugLayer();
                dxg_flactory_flags |= DXGI_CREATE_FACTORY_DEBUG;
            }
#endif

        ComPtr<IDXGIFactory7> factory;
        ASSERT_SUCCEEDED(CreateDXGIFactory2(dxg_flactory_flags, MY_IID_PPV_ARGS(&factory)));
        if (!setting.use_wrap_device)
            {
                ComPtr<IDXGIAdapter4> hardware_adapter;
                for (UINT adp_index = 0; SUCCEEDED(factory->EnumAdapterByGpuPreference(adp_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                                                                                       MY_IID_PPV_ARGS(&hardware_adapter)));
                     ++adp_index)
                    {
                        DXGI_ADAPTER_DESC1 desc;
                        hardware_adapter->GetDesc1(&desc);

                        if (desc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
                            {
                                continue;
                            }

                        if (SUCCEEDED(D3D12CreateDevice(hardware_adapter.Get(), D3D_FEATURE_LEVEL_11_0, MY_IID_PPV_ARGS(&d3d12_device))))
                            {
                                break;
                            }
                    }
            }

        if (d3d12_device == nullptr)
            {
                ComPtr<IDXGIAdapter> wrap_adapter;
                ASSERT_SUCCEEDED(factory->EnumWarpAdapter(MY_IID_PPV_ARGS(&wrap_adapter)));
                ASSERT_SUCCEEDED(D3D12CreateDevice(wrap_adapter.Get(), D3D_FEATURE_LEVEL_11_0, MY_IID_PPV_ARGS(&d3d12_device)));
            }

        RefCountPtr<ICommandQueue> p_command_queue;
        CreateCommandQueue(d3d12_device.Get(), &p_command_queue);

        auto command_queue_d3d12 = p_command_queue.RawPtr<ICommandQueueD3D12>();
        auto p_device = MakeReferenceCounter<RenderDeviceD3D12>()(setting, d3d12_device.Get(), command_queue_d3d12);
        p_device->QueryInterface(IRenderDevice::IRenderDevice_UUID, reinterpret_cast<IObject**>(pp_device));

        auto p_device_context = MakeReferenceCounter<DeviceContextD3D12>()(p_device);

        p_device_context->QueryInterface(IDeviceContext::IRenderDevice_UUID, reinterpret_cast<IObject**>(pp_context));
    }

    void CreateSwapChain(
        const EngineSetting& setting, IRenderDevice* p_device, IDeviceContext* p_context, void* hwnd, ISwapChain** pp_swapchain) override
    {
        auto p_device_d3d12 = Debug::CheckDynamicPointerCast<IRenderDeviceD3D12, IRenderDevice>(p_device);
        auto p_context_d3d12 = Debug::CheckDynamicPointerCast<IDeviceContextD3D12, IDeviceContext>(p_context);
        auto raw_ptr = MAKE_REF_OBJECT(SwapChainD3D12, Engine::DefaultMemoryAllocator::GetGobalAllocator(), "SwapChainD3D12 Instance")(
            p_device_d3d12, p_context_d3d12, hwnd);

        raw_ptr->QueryInterface(ISwapChain::ISwapChain_UUID, reinterpret_cast<IObject**>(pp_swapchain));
    }

    void CreateCommandQueue(ID3D12Device* d3d12_device, ICommandQueue** pp_command_queue) override
    {
        ComPtr<ID3D12CommandQueue> p_d3d12_command_queue;
        COMMAND_QUEUE_DESC queue_desc;
        queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        ASSERT_SUCCEEDED(d3d12_device->CreateCommandQueue(&queue_desc, MY_IID_PPV_ARGS(&p_d3d12_command_queue)));

        ComPtr<ID3D12Fence> p_d3d12_fence;
        ASSERT_SUCCEEDED(d3d12_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, MY_IID_PPV_ARGS(&p_d3d12_fence)));

        auto raw_ptr = MAKE_REF_OBJECT(CommandQueueD3D12, Engine::DefaultMemoryAllocator::GetGobalAllocator(),
                                       "CommandQueueD3D12 Instance")(p_d3d12_command_queue.Get(), p_d3d12_fence.Get());

        raw_ptr->QueryInterface(ICommandQueue::ICommandQueue_UUID, reinterpret_cast<IObject**>(pp_command_queue));
    }
};
}  // namespace Toy::Graphics
Toy::Graphics::ID3D12Factory* GetD3D12Factory() { return Toy::Graphics::D3D12Factory::GetInstance(); }
