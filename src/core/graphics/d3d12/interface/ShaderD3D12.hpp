#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <IShader.hpp>
#include <memory>
#include "DeviceObject.hpp"
#include "ShaderInfos.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
// -> shader bytecode
// -> shader ionfo (reflection infos)
class ShaderD3D12 : public DeviceObject<IShader>
{
    using TBase = DeviceObject<IShader>;

    ShaderResourceBindingRangs resources_rangs;

    ShaderDesc desc;

    Engine::RefCountPtr<Engine::IDataBlob> p_shader_bytecode;

    std::vector<D3D12_INPUT_ELEMENT_DESC> vertex_input_layout;

    IMPLEMENT_CONSTRUCT_STATEMENT(ShaderD3D12, const ShaderCreateInfo& shaer_create_info);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();

    const ShaderDesc& GetDesc() const override;

    const void GetVertexInputLayout(D3D12_INPUT_ELEMENT_DESC** pp_input_layout, std::size_t& inputs) const;

   private:
    void ReflectionShader(Engine::IDataBlob* p_shader_bytecode);
    void CreatePSOInputLayout(const D3D12_SHADER_DESC& shader_desc, ID3D12ShaderReflection* p_reflection);
};
}  // namespace Toy::Graphics