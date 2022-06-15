#include "PipelineState.hpp"
#include <DebugUtility.hpp>
#include <GlobalEnvironment.hpp>
#include <GraphicsDef.hpp>
#include <IApp.hpp>
#include <IGraphics.hpp>
#include "Utility.hpp"

using namespace Toy::Graphics;

void PipelineStateCached::OnDestroy() { pipelinestates_map.clear(); }

ID3D12PipelineState* PipelineStateCached::GetPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc)
{
    auto ps = pipelinestates_map.try_emplace(desc);
    if (ps.second)
        {
            // create new
            auto graphics = Toy::Engine::IApp::env->GetGraphics();
            ASSERT_SUCCEEDED(graphics->GetDevice()->CreateGraphicsPipelineState(&desc, MY_IID_PPV_ARGS(&ps.first->second)));
        }

    return ps.first->second.Get();
}