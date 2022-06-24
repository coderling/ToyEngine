#include "ShaderD3D12.hpp"

namespace Toy::Graphics
{
IMPLEMENT_CONSTRUCT_DEFINE_HEAD(TBase, ShaderD3D12, const ShaderCreateInfo& shader_create_info)
{
    if (shader_create_info.file_path != nullptr || shader_create_info.source != nullptr && shader_create_info.source_length > 0)
        {
            if (shader_create_info.load_bytecode)
                {
                    // load file frome binary file
                }
        }
    else if (shader_create_info.p_shader_bytecode != nullptr)
        {
        }
    else
        {
            LOG_ERROR_EXCEPTION("error in create shader, need file_path or source or bytecode here!!!");
        }
}

IMPLEMENT_QUERYINTERFACE(ShaderD3D12, TBase)
}  // namespace Toy::Graphics
