#pragma once
#include "EngineSetting.hpp"
#include "IRenderDevice.hpp"
#include "RefCountPtr.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
template <typename TypeTraits>
requires std::derived_from<typename TypeTraits::RenderDeviceInterfaceType, IRenderDevice>
class RenderDeviceBase : public Engine::TObject<typename TypeTraits::RenderDeviceInterfaceType>
{
    using TBase = Engine::TObject<typename TypeTraits::RenderDeviceInterfaceType>;
    using CommandQueueInterface = typename TypeTraits::CommandQueueInterfaceType;

   protected:
    Engine::RefCountPtr<CommandQueueInterface> p_command_queue;

   protected:
    RenderDeviceBase(IReferenceCounter* p_refcounter, const EngineSetting& setting, CommandQueueInterface* _p_command_queue)
        : TBase(p_refcounter),
          p_command_queue{_p_command_queue}
    {
    }
};
}  // namespace Toy::Graphics