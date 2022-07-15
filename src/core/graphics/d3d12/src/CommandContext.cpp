#include "CommandContext.hpp"
#include "Utility.hpp"

namespace Toy::Graphics
{
CommandContext::CommandContext(IRenderDeviceD3D12 *device, const D3D12_COMMAND_LIST_TYPE &list_type, const UINT &node_mask)
{
    auto d3d12_device = device->GetDevice();
    ASSERT_SUCCEEDED(d3d12_device->CreateCommandAllocator(list_type, MY_IID_PPV_ARGS(&p_command_allocator)));
    ASSERT_SUCCEEDED(
        d3d12_device->CreateCommandList(node_mask, list_type, p_command_allocator.Get(), nullptr, MY_IID_PPV_ARGS(&p_command_list)));
    this->Close();
}

void CommandContext::SetPipelineState(ID3D12PipelineState *pso)
{
    if (p_current_pso != pso)
        {
            p_command_list->SetPipelineState(pso);
            p_current_pso = pso;
        }
}

void CommandContext::SetDescriptorHeap(ID3D12DescriptorHeap *_p_srv_cbv_uav_heap, ID3D12DescriptorHeap *_p_sampler_heap)
{
    ENGINE_ASSERT_EXPR(_p_srv_cbv_uav_heap == nullptr || _p_srv_cbv_uav_heap->GetDesc().Type == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    ENGINE_ASSERT_EXPR(_p_sampler_heap == nullptr || _p_sampler_heap->GetDesc().Type == D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

    static ID3D12DescriptorHeap *heaps[2]{nullptr, nullptr};
    uint32_t index = 0;
    heaps[index] = _p_srv_cbv_uav_heap;
    if (_p_srv_cbv_uav_heap != nullptr)
        {
            ++index;
        }

    heaps[index] = _p_sampler_heap;
    if (_p_sampler_heap != nullptr)
        {
            ++index;
        }

    p_srv_cbv_uav_heap = _p_srv_cbv_uav_heap;
    p_sampler_heap = _p_sampler_heap;
    p_command_list->SetDescriptorHeaps(index, heaps);
}

void CommandContext::Reset()
{
    ASSERT_SUCCEEDED(p_command_allocator->Reset());
    ASSERT_SUCCEEDED(p_command_list->Reset(p_command_allocator.Get(), nullptr));
}

void CommandContext::Close()
{
    auto hr = p_command_list->Close();
    ENGINE_DEV_CHECK_EXPR_FORMAT(SUCCEEDED(hr), "faile to close command list(hr = {:#08X})", (unsigned long)hr);
}

ID3D12GraphicsCommandList *CommandContext::GetCommandList() const noexcept { return p_command_list.Get(); }
}  // namespace Toy::Graphics