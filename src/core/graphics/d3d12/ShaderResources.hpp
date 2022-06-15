#pragma once
#include <stdint.h>

namespace Toy::Graphics
{
// describe a shader resours in shader
struct ShaderResourceAttrib
{
    const char* const name;
    const uint32_t bind_point;
    const uint32_t bind_count;
    const uint32_t space;
};

// contain a shader use all resource infos, create by D3D12 reflecttion
class ShaderResources
{
};
}  // namespace Toy::Graphics