#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IShader.hpp>
#include <memory>
#include "ShaderResources.hpp"
#include "TObject.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
// -> shader bytecode
// -> shader ionfo (reflection infos)
class ShaderD3D12 : public Engine::TObject<IShader>
{
    using TBase = Engine::TObject<IShader>;
    ShaderResources p_resourecs;

    ShaderDesc desc;

    IMPLEMENT_CONSTRUCT_STATEMENT(ShaderD3D12, const ShaderCreateInfo& shaer_create_info);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    const ShaderDesc& GetDesc() const override;
};
}  // namespace Toy::Graphics