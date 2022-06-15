#include "FrameReource_D3D12.hpp"

using namespace Toy::Graphics;

void FrameResource::Create() { command_list = std::make_unique<GraphicsCommandList>(); }

IGraphicsCommandList* FrameResource::GetCommandList() { return command_list.get(); }

void FrameResource::OnDestroy() {}