#pragma once

#include "GraphicsDef.hpp"
#include "IObject.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
class IGPUResource
{
   public:
    virtual IDeviceResource* GetResource() = 0;
    virtual const IDeviceResource* GetResource() const = 0;
    virtual IDeviceResource** GetAddressOf() = 0;
    virtual GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const = 0;
    virtual void Release() = 0;
};
}  // namespace Toy::Graphics
