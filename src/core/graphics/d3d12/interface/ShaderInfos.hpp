#pragma once
#include <d3d12.h>
#include <d3d12shader.h>
#include <cstdlib>
#include <memory>
#include <vector>

namespace Toy::Graphics
{
struct ShaderPSOInputLayout
{
    std::unique_ptr<D3D12_INPUT_ELEMENT_DESC[]> input_elements;
    std::size_t num;

    ShaderPSOInputLayout() noexcept : input_elements{nullptr}, num{0} {}
};

struct ShaderResourceRangs
{
    struct ResourceRang
    {
        static constexpr const uint32_t Shader_InputType_Bits = 4;  // max value is: D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = 11
        static constexpr const uint32_t SRV_Dismension_Bit = 4;     // max value is: D3D_SRV_DIMENSION_BUFFEREX = 11

        const char* const name;
        const uint16_t bind_point;
        const uint16_t bind_count;
        const uint16_t space;
        const uint32_t shader_type : Shader_InputType_Bits;
        const uint32_t dimension : SRV_Dismension_Bit;
    };

    using TRanges = std::vector<ResourceRang>;
    TRanges rangs;

    void Add(const uint16_t& bind_point, const uint16_t& bind_count, const uint16_t& space, const D3D_SHADER_INPUT_TYPE& input_type,
             const D3D_SRV_DIMENSION& dimension)
    {
    }
};
}  // namespace Toy::Graphics