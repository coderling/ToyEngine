#pragma once
#include "IRenderDevice.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
template <typename RenderDeviceImpType>
requires std::derived_from<RenderDeviceImpType, IRenderDevice>
class RenderDeviceBase : public Engine::TObject<RenderDeviceImpType>
{
    using TBase = Engine::TObject<RenderDeviceImpType>;

   public:
    RenderDeviceBase(IReferenceCounter* p_refcounter) : TBase(p_refcounter) {}
};
}  // namespace Toy::Graphics