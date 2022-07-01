#pragma once
#include "IShader.hpp"

namespace Toy::Graphics
{
// collection graphics pipeline / compute pipeline rootsignture resource info.
class ShaderResourceMaping
{
    void Init(IShader* vs, IShader* hs, IShader* ds, IShader* gs, IShader* ps);

    void Init(IShader* cs);

    void Clear();

    void Append(IShader* p_shader);
};
}  // namespace Toy::Graphics