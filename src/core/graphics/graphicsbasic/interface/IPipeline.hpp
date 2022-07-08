#pragma once

#include <memory>
#include "IObject.hpp"
#include "PipelineFragment.hpp"

namespace Toy::Graphics
{
class IPipeline : public Toy::IObject
{
   public:
    INTERFACEUUID(IPipeline) = {/* b3acc324-fa9d-4ddd-b357-1dacf70160bd */
                                0xb3acc324,
                                0xfa9d,
                                0x4ddd,
                                {0xb3, 0x57, 0x1d, 0xac, 0xf7, 0x01, 0x60, 0xbd}};
    static IPipeline* GetInstance();
    virtual int Initialize() = 0;
    virtual void Tick() = 0;
    virtual void AddPipelineFragment(PipelineFragment* fg) = 0;

   protected:
    virtual void Render() = 0;
    virtual void BeforeRender() = 0;
    virtual void AfterRender() = 0;
};
}  // namespace Toy::Graphics