#pragma once

#include "IShader.hpp"

namespace Toy::Graphics
{

enum EShaderResourceType
{
    ShaderResourceType_PerDraw = 0,
    ShaderResourceType_PerMaterial = 1,
    ShaderResourceType_Static = 2,
};

struct ShaderResourceVaribleDesc
{
    SHADER_TYPE shader_type{SHADER_TYPE_UNKNOWN};
    EShaderResourceType res_type{ShaderResourceType_Static};
    const char* name{nullptr};
};

struct ShaderResourceLayoutDesc
{
    ShaderResourceVaribleDesc* shader_descs;
    uint16_t num_shader_descs;
};

struct PipelineStateCreateInfo
{
    IShader* p_vs = nullptr;
    IShader* p_hs = nullptr;
    IShader* p_ds = nullptr;
    IShader* p_gs = nullptr;
    IShader* p_ps = nullptr;

    IShader* p_cs = nullptr;

    ShaderResourceLayoutDesc resource_layout_desc;
};
}  // namespace Toy::Graphics