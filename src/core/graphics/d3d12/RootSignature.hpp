#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DebugUtility.hpp>
#include <HashUtils.hpp>
#include <IObject.hpp>
#include <unordered_map>
#include <vector>

namespace Toy::Graphics
{
class RootParameter
{
    friend class RootSignature;

    D3D12_ROOT_PARAMETER params;

   public:
    RootParameter() noexcept { params.ParameterType = (D3D12_ROOT_PARAMETER_TYPE)0xFFFFFFFF; }
    ~RootParameter() noexcept { Clear(); }
    void Clear()
    {
        if (params.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
            {
                delete[] params.DescriptorTable.pDescriptorRanges;
            }
        params.ParameterType = (D3D12_ROOT_PARAMETER_TYPE)0xFFFFFFFF;
    }

    void SetParamsTypeAndRegister(const D3D12_ROOT_PARAMETER_TYPE& type, const UINT& _register,
                                  const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL, const UINT& space = 0)
    {
        params.ParameterType = type;
        params.ShaderVisibility = visiability;
        params.Constants.ShaderRegister = _register;
        params.Constants.RegisterSpace = 0;
    }

    void InitAsConstants(const UINT& _register, const UINT& num_words,
                         const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL, const UINT& space = 0)
    {
        SetParamsTypeAndRegister(D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS, _register, visiability, space);
        params.Constants.Num32BitValues = num_words;
    }

    void InitAsConstantBuffer(const UINT& _register, const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL,
                              const UINT& space = 0)
    {
        SetParamsTypeAndRegister(D3D12_ROOT_PARAMETER_TYPE_CBV, _register, visiability, space);
    }

    void InitAsBufferSRV(const UINT& _register, const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL,
                         const UINT& space = 0)
    {
        SetParamsTypeAndRegister(D3D12_ROOT_PARAMETER_TYPE_SRV, _register, visiability, space);
    }

    void InitAsBufferUAV(const UINT& _register, const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL,
                         const UINT& space = 0)
    {
        SetParamsTypeAndRegister(D3D12_ROOT_PARAMETER_TYPE_UAV, _register, visiability, space);
    }

    void InitAsDescriptorTable(const UINT& range_count, const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL)
    {
        params.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        params.ShaderVisibility = visiability;
        params.DescriptorTable.NumDescriptorRanges = range_count;
        params.DescriptorTable.pDescriptorRanges = new D3D12_DESCRIPTOR_RANGE[range_count];
    }

    void SetTableRange(const UINT& range_index, const D3D12_DESCRIPTOR_RANGE_TYPE& type, const UINT& _register, const UINT& count,
                       const UINT& space)
    {
        ENGINE_ASSERT_EXPR(params.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE);
        D3D12_DESCRIPTOR_RANGE* range = const_cast<D3D12_DESCRIPTOR_RANGE*>(params.DescriptorTable.pDescriptorRanges + range_index);
        range->RangeType = type;
        range->NumDescriptors = count;
        range->BaseShaderRegister = _register;
        range->RegisterSpace = space;
        range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    }

    void InitAsDescriptorRange(const D3D12_DESCRIPTOR_RANGE_TYPE& type, const UINT& _register, const UINT& count,
                               const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL, const UINT& space = 0)
    {
        InitAsDescriptorTable(1, visiability);
        SetTableRange(0, type, _register, count, space);
    }

    std::size_t GetHash();
};

class RootTableParameter
{
    friend class RootSignature;

    D3D12_ROOT_PARAMETER params;
    std::vector<D3D12_DESCRIPTOR_RANGE> ranges;

   public:
    RootTableParameter() noexcept { params.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; }
    void SetVisiable(const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL) noexcept
    {
        params.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        params.ShaderVisibility = visiability;
    }

    void ExtendAsDescriptorTable(const UINT& range_count)
    {
        params.DescriptorTable.NumDescriptorRanges = range_count;
        ranges.resize(range_count);
        params.DescriptorTable.pDescriptorRanges = ranges.data();
    }

    void SetTableRange(const UINT& range_index, const D3D12_DESCRIPTOR_RANGE_TYPE& type, const UINT& _register, const UINT& count,
                       const UINT& space)
    {
        ENGINE_DEV_CHECK_EXPR(range_index >= 0, "range index must >= 0");
        UINT offset = 0;
        if (range_index > 0)
            {
                offset = ranges[range_index].OffsetInDescriptorsFromTableStart + ranges[range_index].NumDescriptors;
            }
        if (range_index) ENGINE_ASSERT_EXPR(params.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE);
        D3D12_DESCRIPTOR_RANGE* range = const_cast<D3D12_DESCRIPTOR_RANGE*>(params.DescriptorTable.pDescriptorRanges + range_index);
        range->RangeType = type;
        range->NumDescriptors = count;
        range->BaseShaderRegister = _register;
        range->RegisterSpace = space;
        range->OffsetInDescriptorsFromTableStart = offset;
    }

    std::size_t GetHash();
};

using namespace Microsoft::WRL;
class RootSignature final
{
    // root signature max num support
    static constexpr const std::size_t MAX_PARAMS_COUNT = 32;
    // D3D12_SHADER_VISIBILITY_MESH = 7
    static constexpr uint32_t MAX_SHADER_VISIBILITY_COUNT = 8;

    std::vector<RootParameter> params;
    std::size_t max_num_params;
    std::vector<RootTableParameter> table_params;
    std::size_t max_num_tables;
    std::vector<D3D12_STATIC_SAMPLER_DESC> static_samplers;
    std::size_t max_num_samplers;

    uint32_t hash_shader_visibility[MAX_SHADER_VISIBILITY_COUNT];
    // table resources count
    uint32_t descriptor_table_size[MAX_PARAMS_COUNT];
    uint32_t descriptor_table_bitmask;
    uint32_t descriptor_sampler_bitmask;
    bool is_build;
    std::size_t hash_code;

   private:
    class RootSignatureCached
    {
        std::unordered_map<std::size_t, ComPtr<ID3D12RootSignature>> cached_rootsignature;

       public:
        void OnRootSignatureDestroy(const RootSignature& rs);
        ID3D12RootSignature* GetRootSignatuer(const std::size_t& hash_code, const D3D12_ROOT_SIGNATURE_DESC& desc);
    };

    static RootSignatureCached root_signature_cached;

   public:
    RootSignature() noexcept;
    ~RootSignature() noexcept;

    void Init(const std::size_t& num_views, const std::size_t& num_tables, const std::size_t& num_static_samplers);

    void AddStaticSampler(const UINT& _register, const D3D12_SAMPLER_DESC& non_static_desc,
                          const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL);
    void AddConstantsView(const UINT& _register, const UINT& num_words,
                          const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL, const UINT& space = 0);

    void AddRootView(const D3D12_ROOT_PARAMETER_TYPE& type, const UINT& _register,
                     const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL, const UINT& space = 0);

    void AddDescriptorTable(const UINT& range_count, const D3D12_SHADER_VISIBILITY& visiability = D3D12_SHADER_VISIBILITY_ALL);

    void DoBuild();

    std::size_t GetHash() const;
};

}  // namespace Toy::Graphics