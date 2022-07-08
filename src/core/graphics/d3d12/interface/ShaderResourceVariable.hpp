#pragma once
#include <string_view>
#include "GPUResourceD3D12.hpp"

namespace Toy::Graphics
{
class ShaderResourceVariable final
{
   public:
    void BindResource(const std::string_view& name);
};
}  // namespace Toy::Graphics