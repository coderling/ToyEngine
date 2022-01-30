#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"

namespace Toy::Graphics
{
	class IGraphicsCommandList : public Toy::Engine::IObject
	{
	public:
		virtual IDeviceCommandList* GetDeviceList() const noexcept = 0;
	};
}