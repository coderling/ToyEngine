#include "ShaderD3D12.hpp"
#include "DXCCompiler.hpp"
#include "DataBlob.hpp"
#include "DebugUtility.hpp"
#include "File.hpp"
#include "FileSystem.hpp"
#include "ID3D12Factory.hpp"
#include "Utility.hpp"

namespace Toy::Graphics
{
IMPLEMENT_CONSTRUCT_DEFINE_HEAD(TBase, ShaderD3D12, const ShaderCreateInfo& shader_create_info), desc{shader_create_info.desc.name,
                                                                                                      shader_create_info.desc.shader_type}
{
    if (shader_create_info.file_path != nullptr || shader_create_info.source != nullptr && shader_create_info.source_length > 0)
        {
            static auto DoShaderCompile = [](Engine::IDataBlob** pp_shader_bytecode, const void* buffer, const std::size_t& length,
                                             const wchar_t* entry, const wchar_t* shader_model, const ShaderMacro* macro) {
                ID3D12Factory* factory = GetD3D12Factory();
                Engine::RefCountPtr<IDXCCompiler> p_dxc;
                factory->CreateDXCCompiler(&p_dxc);
                auto args = p_dxc->GetArgsHandle(nullptr);
                args->Assign(buffer, length);
                args->SetEntry(entry);
                args->SetShaderModel(shader_model);
                args->EnableDebug();

                if (macro != nullptr)
                    {
                        for (auto* p_macro = macro; p_macro->macro != nullptr; ++p_macro)
                            {
                                args->AddMacro(Str2Wstr(p_macro->macro).c_str());
                            }
                    }

                TOY_RESULT tr;
                p_dxc->Compile(pp_shader_bytecode, nullptr, tr);
            };

            if (shader_create_info.source == nullptr || shader_create_info.source_length == 0)
                {
                    // load file source / bytecode
                    if (shader_create_info.file_path == nullptr)
                        {
                            LOG_ERROR("expected valid file path or source buffer!!!");
                            return;
                        }

                    auto file = IO::FileSystem::Open(shader_create_info.file_path, IO::EFileAccess::READ);
                    if (shader_create_info.load_bytecode)
                        {
                            // load bytecode from file
                            auto blob = Engine::DataBlob::Create(file.GetLength());
                            file.ReadBlob(blob);
                            p_shader_bytecode.Attach(blob.Detach());
                        }
                    else
                        {
                            // load file and compile
                            std::vector<uint8_t> raw_data;
                            raw_data.resize(file.GetLength());
                            file.ReadRaw(raw_data.data(), file.GetLength());
                            DoShaderCompile(&p_shader_bytecode, raw_data.data(), raw_data.size(),
                                            Str2Wstr(shader_create_info.entry).c_str(),
                                            Str2Wstr(shader_create_info.GetShaderModelString()).c_str(), shader_create_info.macro);
                        }
                }
            else  // if (shader_create_info.source != nullptr && shader_create_info.source_length > 0)
                {
                    DoShaderCompile(&p_shader_bytecode, shader_create_info.source, shader_create_info.source_length,
                                    Str2Wstr(shader_create_info.entry).c_str(), Str2Wstr(shader_create_info.GetShaderModelString()).c_str(),
                                    shader_create_info.macro);
                }
        }
    else if (shader_create_info.p_shader_bytecode != nullptr)
        {
            p_shader_bytecode = shader_create_info.p_shader_bytecode;
        }
    else
        {
            LOG_ERROR_EXCEPTION("error in create shader, need file_path or source or bytecode here!!!");
        }

    desc = shader_create_info.desc;

    ReflectionShader(p_shader_bytecode);
}

IMPLEMENT_QUERYINTERFACE(ShaderD3D12, TBase, IShader)

void ShaderD3D12::ReflectionShader(Engine::IDataBlob* p_shader_bytecode)
{
    ComPtr<IDxcLibrary> p_library = nullptr;
    ComPtr<IDxcBlobEncoding> p_source = nullptr;
    ComPtr<IDxcContainerReflection> p_container_reflection = nullptr;
    ComPtr<ID3D12ShaderReflection> p_reflection = nullptr;
    UINT shaderIdx = 0;
    ASSERT_SUCCEEDED(DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&p_library)));
    ASSERT_SUCCEEDED(p_library->CreateBlobWithEncodingOnHeapCopy(p_shader_bytecode->GetDataPointer(), p_shader_bytecode->GetDataSize(),
                                                                 DXC_CP_ACP, &p_source));
    ASSERT_SUCCEEDED(DxcCreateInstance(CLSID_DxcContainerReflection, IID_PPV_ARGS(&p_container_reflection)));
    ASSERT_SUCCEEDED(p_container_reflection->Load(p_source.Get()));
    ASSERT_SUCCEEDED(p_container_reflection->FindFirstPartKind(DXCCompiler::DxilFourCC::DFCC_DXIL, &shaderIdx));
    ASSERT_SUCCEEDED(p_container_reflection->GetPartReflection(shaderIdx, IID_PPV_ARGS(&p_reflection)));

    D3D12_SHADER_DESC d3d_shader_desc;
    auto hr = p_reflection->GetDesc(&d3d_shader_desc);
    if (FAILED(hr))
        {
            LOG_ERROR("Get Shader_desc failed!");
            return;
        }

    for (std::size_t i; i < d3d_shader_desc.BoundResources; ++i)
        {
            D3D12_SHADER_INPUT_BIND_DESC bind_desc;
            p_reflection->GetResourceBindingDesc(i, &bind_desc);

            switch (bind_desc.Type)
                {
                    case D3D_SIT_CBUFFER:
                        ENGINE_DEV_CHECK_EXPR(bind_desc.BindCount == 1, "Not allow array of constantbuffers");
                        if (bind_desc.BindCount == 1)
                            {
                                resources_rangs.CBVs.Add(bind_desc.Name, bind_desc.BindPoint, bind_desc.BindCount, bind_desc.Space,
                                                         bind_desc.Type, bind_desc.Dimension);
                            }
                        break;
                        ;
                    case D3D_SIT_TEXTURE:
                        resources_rangs.SRVs.Add(bind_desc.Name, bind_desc.BindPoint, bind_desc.BindCount, bind_desc.Space, bind_desc.Type,
                                                 bind_desc.Dimension);
                        break;
                    case D3D_SIT_SAMPLER:
                    case D3D_SIT_STRUCTURED:
                    case D3D_SIT_BYTEADDRESS:
                        resources_rangs.SMPs.Add(bind_desc.Name, bind_desc.BindPoint, bind_desc.BindCount, bind_desc.Space, bind_desc.Type,
                                                 bind_desc.Dimension);
                        break;
                    case D3D_SIT_UAV_RWTYPED:
                    case D3D_SIT_UAV_RWSTRUCTURED:
                    case D3D_SIT_UAV_RWBYTEADDRESS:
                        resources_rangs.UAVs.Add(bind_desc.Name, bind_desc.BindPoint, bind_desc.BindCount, bind_desc.Space, bind_desc.Type,
                                                 bind_desc.Dimension);
                        break;
                        break;
                    default:
                        ENGINE_ASSERT_EXPR("Not Supported ResourceType:", bind_desc.Type);
                        break;
                }
        }

    // if vertex shader, create input layout
    if ((this->desc.shader_type = SHADER_TYPE::SHADER_TYPE_VERTEX))
        {
            CreatePSOInputLayout(d3d_shader_desc, p_reflection.Get());
        }
}

void ShaderD3D12::CreatePSOInputLayout(const D3D12_SHADER_DESC& shader_desc, ID3D12ShaderReflection* p_reflection)
{
    // create pos inputlayout
    // ref:https://blog.techlab-xe.net/dxc-shader-reflection
    auto static get_element_format_handler = [](const D3D_REGISTER_COMPONENT_TYPE& type, const BYTE& component_count, UINT& size) {
        size = 0;
        constexpr static const UINT index_per_component_size[4] = {0, sizeof(UINT), sizeof(INT), sizeof(FLOAT)};
        constexpr static const DXGI_FORMAT Index_DXGI_FORMAT[4][4] = {
            {DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN,
             DXGI_FORMAT_UNKNOWN},  // component_type = D3D_REGISTER_COMPONENT_UNKNOWN

            {DXGI_FORMAT_R32_UINT, DXGI_FORMAT_R32G32_UINT, DXGI_FORMAT_R32G32B32_UINT,
             DXGI_FORMAT_R32G32B32A32_UINT},  // component_type = D3D_REGISTER_COMPONENT_UINT32

            {DXGI_FORMAT_R32_SINT, DXGI_FORMAT_R32G32_SINT, DXGI_FORMAT_R32G32B32_SINT,
             DXGI_FORMAT_R32G32B32A32_SINT},  // component_type = D3D_REGISTER_COMPONENT_SINT32

            {DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT,
             DXGI_FORMAT_R32G32B32A32_FLOAT}  // component_type = D3D_REGISTER_COMPONENT_FLOAT32
        };

        auto va = static_cast<int>(type);
        auto component_index = component_count - 1;
        if (va < 0 || va > 3 || component_index < 0 || component_index > 3)
            {
                return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
            }

        size = index_per_component_size[va] * component_count;
        return Index_DXGI_FORMAT[va][component_index];
    };

    const auto& num_inputs = shader_desc.InputParameters;
    UINT offset = 0;
    vertex_input_layout.resize(num_inputs);
    for (std::size_t i = 0; i < num_inputs; ++i)
        {
            D3D12_SIGNATURE_PARAMETER_DESC param_desc{};
            p_reflection->GetInputParameterDesc(i, &param_desc);

            auto& input_layout = vertex_input_layout[i];
            BYTE component_count = param_desc.Mask;
            component_count = ((component_count & 0xA) >> 1) + (component_count & 0x5);
            component_count = ((component_count & 0xC) >> 2) + (component_count & 0xc);
            UINT size = 0;
            input_layout.SemanticName = param_desc.SemanticName;
            input_layout.Format = get_element_format_handler(param_desc.ComponentType, component_count, size);
            input_layout.InputSlot = 0;  // default zero, range(0-15), can spilt vertexdata for optimization
            input_layout.AlignedByteOffset = offset;
            input_layout.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
            input_layout.SemanticIndex = param_desc.SemanticIndex;
            input_layout.InstanceDataStepRate = 0;  // must zero when inputSlotClass is D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA

            offset += size;
        }
}

}  // namespace Toy::Graphics
