#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"
#include "pch.hpp"
#include <memory>
#include <cstdint>

namespace Toy::Graphics
{
	class TOY_LIB_API IGraphicsCommandList : public Toy::Engine::IObject, public Toy::Engine::NoCopy
	{
	public:
		static std::unique_ptr<IGraphicsCommandList> Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t);
		virtual IDeviceCommandList* GetCmdList() const noexcept = 0;
		virtual void Reset() = 0;
	};
}