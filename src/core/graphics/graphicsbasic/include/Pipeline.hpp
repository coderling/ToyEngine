#pragma once

#include <memory>
#include <unordered_set>
#include "IPipeline.hpp"
#include "PipelineFragment.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
class Pipeline final : public Toy::Engine::TObject<IPipeline>
{
   public:
    int Initialize() override;
    void Tick() override;

    void AddPipelineFragment(PipelineFragment* fg) override;

   private:
    void OnDestroy() override;
    void Render() override;
    void BeforeRender() override;
    void AfterRender() override;
    void TickFuncs();

    void ExecuteFuncs(const PIPELINE_STAGE& st);
    void FinishFrame();

    std::unordered_set<PipelineFragment*> custom_render_funcs;
};
}  // namespace Toy::Graphics