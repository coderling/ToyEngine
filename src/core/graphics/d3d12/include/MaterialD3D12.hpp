#pragma once
#include "IMaterials.hpp"
#include "Shader.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
class MaterialsD3D12 : public Toy::Engine::TObject<IMaterials>
{
    IMPLEMENT_CONSTRUCT_STATEMENT(MaterialsD3D12, ShaderD3D12* p_shader);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();
};
}  // namespace Toy::Graphics