#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"
#include "IGraphicsCommandList.hpp"
#include <array>
#include <cstdint>

namespace Toy::Graphics
{

	class IGraphicsCommandQueue : public Toy::Engine::IObject, public Toy::Engine::NoCopy
	{
	public:
		virtual IDeviceCommandQueue* GetDeviceQueue() const noexcept = 0;
		virtual void ExecuteCommandList(const IGraphicsCommandList* cmd_list) = 0;
		virtual void ExecuteCommandListSync(const IGraphicsCommandList* cmd_list) = 0;
		virtual void ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const *cmd_list) = 0;
		virtual void ExecuteCommandListsSync(const std::size_t& num,  const IGraphicsCommandList* const *cmd_lists) = 0;
		virtual void Signal(std::uint64_t fence_value) = 0;
	};
}
