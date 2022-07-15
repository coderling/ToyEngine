#pragma once

namespace Toy::Graphics
{
class IRenderDeviceD3D12;
class RenderDeviceD3D12;
class IPipelineStateD3D12;
class PipelineStateD3D12;
class IDeviceContextD3D12;
class DeviceContextD3D12;
class ICommandQueueD3D12;
class CommandQueueD3D12;
class ISwapChainD3D12;
class SwapChainD3D12;

struct D3D12TypeTraits final
{
    using RenderDeviceInterfaceType = IRenderDeviceD3D12;
    using RenderDeviceImplType = RenderDeviceD3D12;
    using PipelineStateInterfaceType = IPipelineStateD3D12;
    using PipelineStateImplType = PipelineStateD3D12;
    using DeviceContextInterfaceType = IDeviceContextD3D12;
    using DeviceContextImplType = DeviceContextD3D12;
    using CommandQueueInterfaceType = ICommandQueueD3D12;
    using CommandQueueImplType = CommandQueueD3D12;
    using SwapChainInterfaceType = ISwapChainD3D12;
    using SwapChainImplType = SwapChainD3D12;
};

}  // namespace Toy::Graphics