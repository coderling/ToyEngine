#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"

namespace Toy::Graphics
{
	class IGraphicsCommandQueue : public Toy::Engine::IObject
	{
	public:
		virtual IDeviceCommandQueue* GetDeviceQueue() const noexcept = 0;
	};
}
