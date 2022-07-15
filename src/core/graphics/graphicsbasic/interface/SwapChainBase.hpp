#pragma once

#include "ISwapChain.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
template <typename TypeTraits>
requires std::derived_from<typename TypeTraits::SwapChainInterfaceType, ISwapChain>
class SwapChainBase : public Engine::TObject<typename TypeTraits::SwapChainInterfaceType>
{
    using TBase = Engine::TObject<typename TypeTraits::SwapChainInterfaceType>;
    using DeviceContextInterface = typename TypeTraits::DeviceContextInterfaceType;
    using RenderDeviceInterface = typename TypeTraits::RenderDeviceInterfaceType;

    Engine::RefCountPtr<RenderDeviceInterface> p_render_device;
    Engine::RefCountPtr<DeviceContextInterface> p_device_context;

   protected:
    SwapChainBase(IReferenceCounter* p_refcounter,
                  RenderDeviceInterface* _p_render_device,
                  DeviceContextInterface* _p_device_context,
                  void* hwnd)
        : TBase(p_refcounter),
          p_render_device{_p_render_device},
          p_device_context{_p_device_context}
    {
    }
};
}  // namespace Toy::Graphics