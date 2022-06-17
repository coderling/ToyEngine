#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IShader.hpp>
#include <memory>
#include "ShaderResources.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
// -> shader bytecode
// -> shader ionfo (reflection infos)
class Shader : public IShader
{
    std::unique_ptr<ShaderResources> p_resourecs;
    ComPtr<ID3DBlob> p_bytecode;
    ShaderDesc desc;

   public:
    Shader(const ShaderCreateInfo& create_info);
    const ShaderDesc& GetDesc() const override;
};
}  // namespace Toy::Graphics