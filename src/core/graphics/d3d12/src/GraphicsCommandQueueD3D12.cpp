#include "GraphicsCommandQueueD3D12.hpp"
#include <vector>
#include "GlobalEnvironment.hpp"
#include "IGraphics.hpp"
#include "IReferenceCounter.hpp"
#include "Utility.hpp"

namespace Toy::Graphics
{
IMPLEMENT_QUERYINTERFACE(GraphicsCommandQueueD3D12, TBase)

IMPLEMENT_CONSTRUCT_DEFINE_HEAD(TBase, GraphicsCommandQueueD3D12, const COMMAND_QUEUE_DESC& desc)
{
    auto device = GlobalEnvironment::GetEnv().GetGraphics()->GetDevice();
    ASSERT_SUCCEEDED(device->CreateCommandQueue(&desc, MY_IID_PPV_ARGS(&common_queue)));
    NAME_D3D12_OBJECT(common_queue);
}

void GraphicsCommandQueueD3D12::ExecuteCommandList(const IGraphicsCommandList* cmd_list)
{
    auto device_list = dynamic_cast<ID3D12CommandList*>(cmd_list->GetCmdList());
    common_queue->ExecuteCommandLists(1, &device_list);
}

void GraphicsCommandQueueD3D12::ExecuteCommandListSync(const IGraphicsCommandList* cmd_list)
{
    ExecuteCommandList(cmd_list);
    auto graphics = GlobalEnvironment::GetEnv().GetGraphics();
    graphics->WaitForGpu();
}

void GraphicsCommandQueueD3D12::ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const* cmd_list)
{
    static std::vector<ID3D12CommandList*> pp_list;
    pp_list.clear();
    auto p = cmd_list;
    for (int i = 0; i < num; ++i)
        {
            pp_list.push_back((*p)->GetCmdList());
            p++;
        }
    common_queue->ExecuteCommandLists(num, pp_list.data());
    pp_list.clear();
}

void GraphicsCommandQueueD3D12::ExecuteCommandListsSync(const std::size_t& num, const IGraphicsCommandList* const* cmd_lists)
{
    ExecuteCommandLists(num, cmd_lists);
    auto graphics = GlobalEnvironment::GetEnv().GetGraphics();
    graphics->WaitForGpu();
}

void GraphicsCommandQueueD3D12::Signal(ID3D12Fence* fence, const std::uint64_t& fence_value)
{
    ASSERT_SUCCEEDED(common_queue->Signal(fence, static_cast<UINT64>(fence_value)));
}

void GraphicsCommandQueueD3D12::OnDestroy() {}

}  // namespace Toy::Graphics