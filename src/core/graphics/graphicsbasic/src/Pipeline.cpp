#include "Pipeline.hpp"
#include <IGraphics.hpp>
#include "GlobalEnvironment.hpp"

using namespace Toy::Graphics;

std::unique_ptr<IPipeline> pipeline;

IPipeline* IPipeline::GetInstance()
{
    if (pipeline == nullptr)
        {
            pipeline = std::make_unique<Pipeline>();
        }

    return pipeline.get();
}

int Pipeline::Initialize() { return 0; }

void Pipeline::Finalize()
{
    for (auto it = custom_render_funcs.begin(); it != custom_render_funcs.end(); ++it)
        {
            (*it)->GetHandler()->Unload();
        }
    custom_render_funcs.clear();
}

void Pipeline::Tick()
{
    BeforeRender();
    Render();
    AfterRender();
    FinishFrame();
}

void Pipeline::FinishFrame()
{
    auto graphics = GlobalEnvironment::GetEnv().GetGraphics();
    graphics->FinishFrame();
}

void Pipeline::AddPipelineFragment(PipelineFragment* fg)
{
    auto& funcs = custom_render_funcs;
    if (!funcs.contains(fg))
        {
            funcs.emplace(fg);
            auto handler = fg->GetHandler();
            if (nullptr != handler)
                {
                    handler->Load();
                }
            fg->Resume();
        }
}

void Pipeline::ExecuteFuncs(const PIPELINE_STAGE& st)
{
    auto& funcs = custom_render_funcs;
    for (auto it = funcs.begin(); it != funcs.end();)
        {
            auto fg = *it;
            auto handler = fg->GetHandler();

            if (fg->IsRuning() && nullptr != handler)
                {
                    switch (st)
                        {
                            case PIPELINE_STAGE::BEFORE_RENDER:
                                handler->PreRender();
                                break;
                            case PIPELINE_STAGE::ONRENDER:
                                handler->Render();
                                break;
                                ;
                            case PIPELINE_STAGE::AFTER_RENDER:
                                handler->PostRender();
                                break;
                            default:
                                break;
                        }
                }
        }
}

void Pipeline::TickFuncs()
{
    auto& funcs = custom_render_funcs;
    for (auto it = funcs.begin(); it != funcs.end();)
        {
            auto fg = *it;
            auto handler = fg->GetHandler();

            if (fg->IsRuning() && nullptr != handler)
                {
                    handler->Tick();
                }

            if (fg->IsDead())
                {
                    it = funcs.erase(it);
                    if (nullptr != handler)
                        {
                            handler->Unload();
                        }
                }
            else
                {
                    ++it;
                }
        }
}

void Pipeline::Render() { ExecuteFuncs(PIPELINE_STAGE::ONRENDER); }

void Pipeline::BeforeRender() { ExecuteFuncs(PIPELINE_STAGE::BEFORE_RENDER); }

void Pipeline::AfterRender() { ExecuteFuncs(PIPELINE_STAGE::AFTER_RENDER); }
