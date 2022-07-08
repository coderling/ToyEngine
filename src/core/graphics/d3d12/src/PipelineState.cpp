#include "PipelineState.hpp"
#include <DebugUtility.hpp>
#include <GlobalEnvironment.hpp>
#include <GraphicsDef.hpp>
#include <IApp.hpp>
#include <IRenderDevice.hpp>
#include "Utility.hpp"

using namespace Toy::Graphics;

void PipelineStateCached::OnDestroy() { pipelinestates_map.clear(); }

ID3D12PipelineState* PipelineStateCached::GetPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc) { return nullptr; }