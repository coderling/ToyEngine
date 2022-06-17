#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IFrameResource.hpp>
#include <memory>
#include "GraphicsCommandList_D3D12.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class FrameResource final : public IFrameResource
{
    std::unique_ptr<GraphicsCommandList> command_list;

   public:
    void Create() override;
    IGraphicsCommandList* GetCommandList() override;

   private:
    void OnDestroy() override;
};
}  // namespace Toy::Graphics