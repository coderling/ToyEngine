#pragma once
#include <wrl.h>
#include <IObject.hpp>
#include <unordered_map>
#include "d3dx12.h"

using namespace Microsoft::WRL;
namespace Toy::Graphics
{

class PipelineStateCached final : public Toy::Engine::IObject, public Engine::NoCopy
{
   private:
    std::unordered_map<D3D12_GRAPHICS_PIPELINE_STATE_DESC, ComPtr<ID3D12PipelineState>> pipelinestates_map;

   private:
    PipelineStateCached() = default;
    void OnDestroy() override;

   public:
    ID3D12PipelineState* GetPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc);
    static PipelineStateCached& GetInstance() noexcept;
};
}  // namespace Toy::Graphics