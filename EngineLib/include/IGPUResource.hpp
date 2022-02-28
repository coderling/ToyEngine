#pragma once

#include "GraphicsDef.hpp"
#include "IObject.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
	class IGPUResource : public IObject,public NoCopy
	{
	public:
		virtual IDeviceResource* GetResource() = 0;
		virtual const IDeviceResource* GetResource() const = 0;
		virtual IDeviceResource** GetAddressOf() = 0;
		virtual GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const = 0;
	};
}
