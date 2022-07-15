#pragma once
#include "IPipelineState.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
template <typename TypeTraits>
requires std::derived_from<typename TypeTraits::PipelineStateInterfaceType, IPipelineState>
class PipelineStateBase : public Engine::TObject<typename TypeTraits::PipelineStateInterfaceType>
{
    using TBase = Engine::TObject<typename TypeTraits::PipelineStateInterfaceType>;

   public:
   protected:
    PipelineStateBase(IReferenceCounter* p_refcounter)
        : TBase(p_refcounter)
    {
    }
};
}  // namespace Toy::Graphics