#pragma once
#include "D3D12TypeTraits.hpp"
#include "DeviceContextBase.hpp"
#include "IPipelineStateD3D12.hpp"
#include "IDeviceContextD3D12.hpp"

namespace Toy::Graphics
{
class DeviceContextD3D12 : public DeviceContextBase<D3D12TypeTraits>
{
    using TBase = DeviceContextBase<D3D12TypeTraits>;

   private:
    IMPLEMENT_CONSTRUCT_STATEMENT(DeviceContextD3D12, D3D12TypeTraits::RenderDeviceImplType* device);
};
}  // namespace Toy::Graphics