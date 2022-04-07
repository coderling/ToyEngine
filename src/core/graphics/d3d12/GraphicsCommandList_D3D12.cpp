#include "GraphicsCommandList_D3D12.hpp"
#include "IApp.hpp"
#include "GlobalEnvironment.hpp"
#include "Utility.hpp"

using namespace Toy::Graphics;

std::unique_ptr<IGraphicsCommandList> IGraphicsCommandList::Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t)
{
	return std::make_unique<GraphicsCommandList>(node_mask, t);
}

GraphicsCommandList::GraphicsCommandList()
{
	Create(0, COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
}

GraphicsCommandList::GraphicsCommandList(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t)
{
	Create(node_mask, t);
}

void GraphicsCommandList::OnDestroy()
{

}
		
void GraphicsCommandList::Reset()
{
	ASSERT_SUCCEEDED(command_allocator->Reset());
	ASSERT_SUCCEEDED(command_list->Reset(command_allocator.Get(), nullptr));
}

void GraphicsCommandList::Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t)
{
	auto graphics = Toy::Engine::IApp::env->GetGraphics();
	auto device = graphics->GetDevice();
	ASSERT_SUCCEEDED(device->CreateCommandAllocator(t, MY_IID_PPV_ARGS(&command_allocator)));
	ASSERT_SUCCEEDED(device->CreateCommandList(
		node_mask,
		t,
		command_allocator.Get(),
		nullptr, // initial null pipeline state
		MY_IID_PPV_ARGS(&command_list)));
	command_list->Close();
}
