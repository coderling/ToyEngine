#include "RootSignature.hpp"
#include <GlobalEnvironment.hpp>
#include <IApp.hpp>
#include <IRenderDevice.hpp>
#include "Utility.hpp"

using namespace Toy::Graphics;

// RootSignature cached
RootSignature::RootSignatureCached RootSignature::root_signature_cached;
void RootSignature::RootSignatureCached::OnRootSignatureDestroy(const RootSignature& rs)
{
    // do not destroy current
}

ID3D12RootSignature* RootSignature::RootSignatureCached::GetRootSignatuer(const std::size_t& hash_code,
                                                                          const D3D12_ROOT_SIGNATURE_DESC& desc)
{
    auto iter = cached_rootsignature.find(hash_code);
    if (iter != cached_rootsignature.end())
        {
            return iter->second.Get();
        }

    // new rootsignature
    ComPtr<ID3DBlob> out_blob, error_blob;
    ASSERT_SUCCEEDED(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, out_blob.GetAddressOf(), error_blob.GetAddressOf()));

    auto device = IApp::env->GetGraphics()->GetDevice();

    ID3D12RootSignature* signature = nullptr;
    ASSERT_SUCCEEDED(device->CreateRootSignature(0, out_blob->GetBufferPointer(), out_blob->GetBufferSize(), MY_IID_PPV_ARGS(&signature)));

    cached_rootsignature[hash_code].Attach(signature);
    ENGINE_ASSERT_EXPR(cached_rootsignature.find(hash_code) != cached_rootsignature.end());
    ENGINE_ASSERT_EXPR(cached_rootsignature.find(hash_code)->second.Get() == signature);

    return signature;
}
// RootSignature

RootSignature::RootSignature() noexcept
    : descriptor_table_bitmask(0),
      descriptor_sampler_bitmask(0),
      is_build(false),
      hash_code(0),
      max_num_params(0),
      max_num_tables(0),
      max_num_samplers(0)
{
}

RootSignature::~RootSignature() noexcept { root_signature_cached.OnRootSignatureDestroy(*this); }

void RootSignature::Init(const std::size_t& num_views, const std::size_t& num_tables, const std::size_t& num_static_samplers)
{
    ENGINE_ASSERT_EXPR(is_build == false);
    ENGINE_ASSERT_EXPR(num_views + num_tables <= MAX_PARAMS_COUNT, "current rootsignature supported ", MAX_PARAMS_COUNT, " RootParameters");
    params.reserve(num_views);
    max_num_params = num_views;
    table_params.reserve(num_tables);
    max_num_tables = num_tables;
    static_samplers.reserve(num_static_samplers);
    max_num_samplers = num_static_samplers;
}

void RootSignature::AddStaticSampler(const UINT& _register, const D3D12_SAMPLER_DESC& non_static_desc,
                                     const D3D12_SHADER_VISIBILITY& visiability)
{
    ENGINE_ASSERT_EXPR(static_samplers.size() < max_num_samplers);
    auto& static_desc = static_samplers.emplace_back();
    static_desc.Filter = non_static_desc.Filter;
    static_desc.AddressU = non_static_desc.AddressU;
    static_desc.AddressV = non_static_desc.AddressV;
    static_desc.AddressW = non_static_desc.AddressW;
    static_desc.MipLODBias = non_static_desc.MipLODBias;
    static_desc.MaxAnisotropy = non_static_desc.MaxAnisotropy;
    static_desc.ComparisonFunc = non_static_desc.ComparisonFunc;
    static_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
    static_desc.MinLOD = non_static_desc.MinLOD;
    static_desc.MaxLOD = non_static_desc.MaxLOD;
    static_desc.ShaderRegister = _register;
    static_desc.RegisterSpace = 0;
    static_desc.ShaderVisibility = visiability;

    if (static_desc.AddressU == D3D12_TEXTURE_ADDRESS_MODE_BORDER || static_desc.AddressV == D3D12_TEXTURE_ADDRESS_MODE_BORDER ||
        static_desc.AddressW == D3D12_TEXTURE_ADDRESS_MODE_BORDER)
        {
            ENGINE_DEV_CHECK_EXPR(non_static_desc.BorderColor[0] == 0.0f && non_static_desc.BorderColor[1] == 0.0f &&
                                          non_static_desc.BorderColor[2] == 0.0f && non_static_desc.BorderColor[3] == 0.0f ||

                                      non_static_desc.BorderColor[0] == 0.0f && non_static_desc.BorderColor[1] == 0.0f &&
                                          non_static_desc.BorderColor[2] == 0.0f && non_static_desc.BorderColor[3] == 1.0f ||

                                      non_static_desc.BorderColor[0] == 1.0f && non_static_desc.BorderColor[1] == 1.0f &&
                                          non_static_desc.BorderColor[2] == 1.0f && non_static_desc.BorderColor[3] == 1.0f,
                                  "sampler border color does not match static sampler limitations!");
            if (non_static_desc.BorderColor[3] == 1.0f)
                {
                    if (non_static_desc.BorderColor[0] == 1.0f)
                        {
                            static_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
                        }
                    else
                        {
                            static_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
                        }
                }
            else
                {
                    static_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
                }
        }
}