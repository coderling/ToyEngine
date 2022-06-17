#include "GraphicsCommandQueue_D3D12.hpp"
#include <vector>
#include "GlobalEnvironment.hpp"
#include "IApp.hpp"
#include "IGraphics.hpp"
#include "Utility.hpp"

using namespace Toy::Graphics;

void GraphicsCommandQueue::ExecuteCommandList(const IGraphicsCommandList* cmd_list)
{
    auto device_list = dynamic_cast<ID3D12CommandList*>(cmd_list->GetCmdList());
    common_queue->ExecuteCommandLists(1, &device_list);
}

void GraphicsCommandQueue::ExecuteCommandListSync(const IGraphicsCommandList* cmd_list)
{
    ExecuteCommandList(cmd_list);
    auto graphics = Toy::Engine::IApp::env->GetGraphics();
    graphics->WaitForGpu();
}

void GraphicsCommandQueue::ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const* cmd_list)
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

void GraphicsCommandQueue::ExecuteCommandListsSync(const std::size_t& num, const IGraphicsCommandList* const* cmd_lists)
{
    ExecuteCommandLists(num, cmd_lists);
    auto graphics = Toy::Engine::IApp::env->GetGraphics();
    graphics->WaitForGpu();
}

void GraphicsCommandQueue::Signal(ID3D12Fence* fence, const std::uint64_t& fence_value)
{
    ASSERT_SUCCEEDED(common_queue->Signal(fence, static_cast<UINT64>(fence_value)));
}

void GraphicsCommandQueue::OnDestroy() {}

GraphicsCommandQueue::GraphicsCommandQueue(const COMMAND_QUEUE_DESC* desc)
{
    auto device = Toy::Engine::IApp::env->GetGraphics()->GetDevice();
    ASSERT_SUCCEEDED(device->CreateCommandQueue(desc, MY_IID_PPV_ARGS(&common_queue)));
    NAME_D3D12_OBJECT(common_queue);
}
