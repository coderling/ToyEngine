#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"
#include "IGraphicsCommandList.hpp"
#include <array>

namespace Toy::Graphics
{

	class IGraphicsCommandQueue : public Toy::Engine::IObject, public Toy::Engine::NoCopy
	{
	public:
		virtual IDeviceCommandQueue* GetDeviceQueue() const noexcept = 0;
		virtual void ExecuteCommandList(IGraphicsCommandList* cmd_list) = 0;
		virtual void ExecuteCommandListSync(IGraphicsCommandList* cmd_list) = 0;
		virtual void ExecuteCommandLists(std::size_t num, IGraphicsCommandList* const *cmd_list) = 0;
		virtual void ExecuteCommandListsSync(std::size_t num,  IGraphicsCommandList* const *cmd_lists) = 0;
		virtual void WaitGPU() = 0;
	};
}
