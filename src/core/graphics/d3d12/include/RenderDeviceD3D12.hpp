#pragma once

#include <wrl.h>
#include <memory>
#include <vector>
#include "D3D12TypeTraits.hpp"
#include "DescriptorHeap.hpp"
#include "EngineSetting.hpp"
#include "FenceD3D12.hpp"
#include "ICommandQueueD3D12.hpp"
#include "IPipelineStateD3D12.hpp"
#include "IRenderDeviceD3D12.hpp"
#include "RefCountPtr.hpp"
#include "RenderDeviceBase.hpp"
#include "SwapChainD3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{

class RenderDeviceD3D12 final : public RenderDeviceBase<D3D12TypeTraits>
{
    using TBase = RenderDeviceBase<D3D12TypeTraits>;
    ComPtr<ID3D12Device> p_device;

    // 0: D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
    // 1: D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
    // 2: D3D12_DESCRIPTOR_HEAP_TYPE_RTV
    //  3:D3D12_DESCRIPTOR_HEAP_TYPE_DSV
    CPUDescriptorHeap cpu_descriptorheap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
    // 0: D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
    // 1: D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
    GPUDescriptorHeap gpu_descriptorheap[2];

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    int Initialize() override;

    IDevice* GetDevice() const noexcept override { return p_device.Get(); }
    ICommandQueue* GetCommandQueue() const noexcept override { return p_command_queue.RawPtr(); }
    void WaitForGpu() override;
    void FinishFrame() override;
    template <typename ObjectType, typename = typename std::enable_if<std::is_object<ObjectType>::value>::type>
    void SafeReleaseGPUObject(ObjectType&& object)
    {
    }

    void CreatePipelineState(const PipelineStateCreateInfo& create_info, IPipelineState** pp_pipelinestate) override;

    void CreateShader(const ShaderCreateInfo& create_info, IShader** pp_shader) override;

   protected:
    void OnDestroy() override;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(RenderDeviceD3D12,
                                  const EngineSetting& setting,
                                  ID3D12Device* p_d3d12_device,
                                  ICommandQueueD3D12* p_command_queue);
};
}  // namespace Toy::Graphics
