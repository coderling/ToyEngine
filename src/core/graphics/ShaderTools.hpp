#pragma once
#include <IShader.hpp>

namespace Toy::Graphics
{
inline ShaderCreateInfo ParseShaderCreateInfoFromeSource(const char* source, const std::size_t len);

inline ShaderCreateInfo ParseShaderCreateInfoFromeFile(const char* file_path);
}  // namespace Toy::Graphics