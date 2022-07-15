#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "CommonDefines.hpp"
#include "DebugUtility.hpp"
#include "IRenderDeviceD3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class CommandContext
{
    ComPtr<ID3D12GraphicsCommandList> p_command_list;
    ComPtr<ID3D12CommandAllocator> p_command_allocator;

    ID3D12DescriptorHeap* p_srv_cbv_uav_heap;
    ID3D12DescriptorHeap* p_sampler_heap;

    ID3D12PipelineState* p_current_pso;

   public:
    NOCOPY_AND_NOMOVE(CommandContext);

    CommandContext(IRenderDeviceD3D12* device, const D3D12_COMMAND_LIST_TYPE& list_type, const UINT& node_mask);

    void SetPipelineState(ID3D12PipelineState* pso);

    void SetDescriptorHeap(ID3D12DescriptorHeap* _p_srv_cbv_uav_heap, ID3D12DescriptorHeap* _p_sampler_heap);

    void Reset();

    void Close();

    ID3D12GraphicsCommandList* GetCommandList() const noexcept;
};
}  // namespace Toy::Graphics