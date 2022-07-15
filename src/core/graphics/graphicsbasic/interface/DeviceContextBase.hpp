#pragma once
#include "IDeviceContext.hpp"
#include "TObject.hpp"
#include "RefCountPtr.hpp"

namespace Toy::Graphics
{
template <typename TypeTraits>
requires std::derived_from<typename TypeTraits::DeviceContextInterfaceType, IDeviceContext>
class DeviceContextBase : public Engine::TObject<typename TypeTraits::DeviceContextInterfaceType>
{
    using TBase = typename TypeTraits::DeviceContextInterfaceType;
    using PipelineStateInterface = typename TypeTraits::PipelineStateInterfaceType;

   protected:
    Engine::RefCountPtr<PipelineStateInterface> p_current_PSO;

   public:
    DeviceContextBase(IReferenceCounter* p_refcounter)
        : TBase(p_refcounter)
    {
    }
};
}  // namespace Toy::Graphics