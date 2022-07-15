#pragma once
#include <d3d12.h>
#include <d3d12shader.h>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include "DebugUtility.hpp"

namespace Toy::Graphics
{
struct ShaderPSOInputLayout
{
    std::unique_ptr<D3D12_INPUT_ELEMENT_DESC[]> input_elements;
    std::size_t num;

    ShaderPSOInputLayout() noexcept
        : input_elements{nullptr},
          num{0}
    {
    }
};

// 一种类型的Shader资源
struct SingleShaderResourceRangs
{
    struct ResourceRang
    {
        static constexpr const uint32_t Shader_InputType_Bits = 4;  // max value is: D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = 11
        static constexpr const uint32_t SRV_Dismension_Bit = 4;     // max value is: D3D_SRV_DIMENSION_BUFFEREX = 11

        std::string name;
        uint16_t bind_point;
        uint16_t bind_count;
        uint16_t space;
        uint32_t input_type : Shader_InputType_Bits;
        uint32_t dimension : SRV_Dismension_Bit;
    };

    using TRanges = std::vector<ResourceRang>;
    TRanges rangs;

    void Add(const char* vname,
             const uint16_t& bind_point,
             const uint16_t& bind_count,
             const uint16_t& space,
             const D3D_SHADER_INPUT_TYPE& input_type,
             const D3D_SRV_DIMENSION& dimension)
    {
        ResourceRang rang{vname, bind_point, bind_count, space, static_cast<uint32_t>(input_type), static_cast<uint32_t>(dimension)};
#if ENGINE_DEVELOPMENT
        DebugVerify(rang);
#endif
        rangs.emplace_back(rang);
    }

#if ENGINE_DEVELOPMENT
    void DebugVerify()
    {
        std::size_t i = 0, max = rangs.size();
        for (; i < max; ++i)
            {
                for (auto t = i + 1; t < max; ++t)
                    {
                        auto r1 = rangs[i];
                        auto r2 = rangs[t];
                        if (r1.space != r2.space)
                            {
                                continue;
                                ;
                            }
                        if (r1.bind_point > r2.bind_point)
                            {
                                auto tmp = r1;
                                r1 = r2;
                                r2 = tmp;
                            }

                        if (r1.bind_point < r2.bind_point)
                            {
                                if (r1.bind_point + r1.bind_count > r2.bind_point)
                                    {
                                        LOG_ERROR("Shader Register Overlab!!!{ ", r1.bind_point, ",", r1.bind_count, "} {", r1.bind_point,
                                                  ", ", r2.bind_count, "} on space: ", r1.space);
                                    }
                            }
                    }
            }
    }

    bool DebugVerify(const ResourceRang& rang)
    {
        std::size_t i = 0, max = rangs.size();
        for (; i < max; ++i)
            {
                auto r1 = rang;
                auto r2 = rangs[i];
                if (r1.space != r2.space)
                    {
                        continue;
                        ;
                    }

                if (r1.bind_point > r2.bind_point)
                    {
                        auto tmp = r1;
                        r1 = r2;
                        r2 = tmp;
                    }

                if (r1.bind_point < r2.bind_point)
                    {
                        if (r1.bind_point + r1.bind_count > r2.bind_point)
                            {
                                LOG_ERROR("Shader Register Overlab!!!{ ", r1.bind_point, ",", r1.bind_count, "} {", r1.bind_point, ", ",
                                          r2.bind_count, "} on space: ", r1.space);
                                return false;
                            }
                    }
            }
        return true;
    }
#endif
};

struct ShaderResourceBindingRangs
{
    SingleShaderResourceRangs CBVs;  // CBV
    SingleShaderResourceRangs SRVs;  // SRV
    SingleShaderResourceRangs UAVs;  // UAV
    SingleShaderResourceRangs SMPs;  // sampler
};

}  // namespace Toy::Graphics