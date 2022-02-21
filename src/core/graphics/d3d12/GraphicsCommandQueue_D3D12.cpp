#include "GraphicsCommandQueue_D3D12.hpp"
#include "../../interface/IApp.hpp"
#include "../../interface/GlobalEnvironment.hpp"
#include "IGraphics.hpp"
#include "Utility.hpp"

using namespace Toy::Graphics;

void GraphicsCommandQueue::ExecuteCommandList(IGraphicsCommandList* cmd_list)
{

}

void GraphicsCommandQueue::ExecuteCommandListSync(IGraphicsCommandList* cmd_list)
{

}

void GraphicsCommandQueue::ExecuteCommandLists(std::size_t num, IGraphicsCommandList* const* cmd_list)
{

}

void GraphicsCommandQueue::ExecuteCommandListsSync(std::size_t num, IGraphicsCommandList* const* cmd_lists)
{

}

void GraphicsCommandQueue::WaitGPU()
{

}

void GraphicsCommandQueue::Destroy()
{

}

GraphicsCommandQueue::GraphicsCommandQueue(const COMMAND_QUEUE_DESC* desc)
{
	auto device = Toy::Engine::IApp::env->GetGraphics()->GetDevice();
	ASSERT_SUCCEEDED(device->CreateCommandQueue(desc, MY_IID_PPV_ARGS(&common_queue)));
	NAME_D3D12_OBJECT(common_queue);
}
