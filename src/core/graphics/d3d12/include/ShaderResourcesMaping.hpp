#pragma once
#include <d3d12.h>
#include <dxgi.h>
#include <vector>
#include "IShader.hpp"
#include "d3dx12.h"

namespace Toy::Graphics
{
// collection graphics pipeline / compute pipeline rootsignture resource info.
class ShaderResourceMaping
{
    // rootsignature size limit, so max 64 parameters
    CD3DX12_ROOT_PARAMETER root_parameters[64];

   public:
    void Init(IShader* vs, IShader* hs, IShader* ds, IShader* gs, IShader* ps);

    void Init(IShader* cs);

    void Clear();

    void Append(IShader* p_shader);
};
}  // namespace Toy::Graphics