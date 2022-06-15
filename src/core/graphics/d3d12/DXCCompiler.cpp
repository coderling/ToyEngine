#include <string.h>
#include <CStringTool.hpp>
#include <functional>
#include "DXCComplier.hpp"
#include "Utility.hpp"

using namespace Toy::Graphics;

void DXCCompiler::Compile(const DXCCompileArgs& args)
{
    ComPtr<IDxcUtils> p_utils = nullptr;
    ComPtr<IDxcCompiler3> p_compiler = nullptr;
    DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&p_utils));
    DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&p_compiler));

    ComPtr<IDxcIncludeHandler> p_include_handler = nullptr;
    p_utils->CreateDefaultIncludeHandler(&p_include_handler);

    ComPtr<IDxcBlobEncoding> p_source = nullptr;
    auto hr = p_utils->LoadFile(Str2Wstr(args.file_path).c_str(), nullptr, &p_source);
    ENGINE_DEV_CHECK_EXPR(SUCCEEDED(hr), "Load file fail:", args.file_path);

    DxcBuffer source_buffer;
    source_buffer.Ptr = p_source->GetBufferPointer();
    source_buffer.Size = p_source->GetBufferSize();
    source_buffer.Encoding = DXC_CP_ACP;  // Autodetect utf8

    ComPtr<IDxcResult> p_result = nullptr;
    hr = p_compiler->Compile(&source_buffer, args.GetArguments(), args.GetArgCount(), p_include_handler.Get(), IID_PPV_ARGS(&p_result));
    ENGINE_ASSERT_EXPR(SUCCEEDED(hr), "compile shader fail", args.file_path);

    ComPtr<IDxcBlobUtf8> p_errors = nullptr;
    hr = p_result->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&p_errors), nullptr);
    LOG_WARNING_EXPR(SUCCEEDED(hr), "error on get error output:", args.file_path);

    std::size_t bytecode_length = 0;
    if (p_errors != nullptr && p_errors->GetStringLength() != 0)
        {
            LOG_ERROR("Shadering Compile Error:", p_errors->GetStringPointer());
        }

    ComPtr<IDxcBlob> p_shader = nullptr;
    ComPtr<IDxcBlobUtf16> p_shader_name = nullptr;

    ASSERT_SUCCEEDED(p_result->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&p_shader), &p_shader_name));
    result.SetShaderCode(p_shader.Get(), p_shader_name.Get());

    ComPtr<IDxcBlob> p_pdb = nullptr;
    ComPtr<IDxcBlobUtf16> p_pdbname = nullptr;
    ASSERT_SUCCEEDED(p_result->GetOutput(DXC_OUT_PDB, IID_PPV_ARGS(&p_pdb), &p_pdbname));
    result.SetPDBCode(p_pdb.Get(), p_pdbname.Get());

    result.hr = S_OK;
}

void DXCCompiler::CreatePSOInputLayout(const D3D12_SHADER_DESC& shader_desc, ShaderPSOInputLayout& layout,
                                       ID3D12ShaderReflection* p_reflection) const
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
    layout.num = num_inputs;
    layout.input_elements.reset(new D3D12_INPUT_ELEMENT_DESC[num_inputs]);

    UINT offset = 0;
    for (std::size_t i = 0; i < num_inputs; ++i)
        {
            D3D12_SIGNATURE_PARAMETER_DESC param_desc{};
            p_reflection->GetInputParameterDesc(i, &param_desc);

            auto& input_layout = layout.input_elements[i];
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

void DXCCompiler::ReflectShader(const D3D12_SHADER_BYTECODE& bytecode, ShaderReflectInfo& out_info) const
{
    ENGINE_ASSERT(bytecode.pShaderBytecode != nullptr && bytecode.BytecodeLength > 0, "null shader bytecode");
    ComPtr<IDxcLibrary> p_library = nullptr;
    ComPtr<IDxcBlobEncoding> p_source = nullptr;
    ComPtr<IDxcContainerReflection> p_container_reflection = nullptr;
    ComPtr<ID3D12ShaderReflection> p_reflection = nullptr;
    UINT shaderIdx = 0;
    ASSERT_SUCCEEDED(DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&p_library)));
    ASSERT_SUCCEEDED(p_library->CreateBlobWithEncodingOnHeapCopy(bytecode.pShaderBytecode, bytecode.BytecodeLength, DXC_CP_ACP, &p_source));
    ASSERT_SUCCEEDED(DxcCreateInstance(CLSID_DxcContainerReflection, IID_PPV_ARGS(&p_container_reflection)));
    ASSERT_SUCCEEDED(p_container_reflection->Load(p_source.Get()));
    ASSERT_SUCCEEDED(p_container_reflection->FindFirstPartKind(DFCC_DXIL, &shaderIdx));
    ASSERT_SUCCEEDED(p_container_reflection->GetPartReflection(shaderIdx, IID_PPV_ARGS(&p_reflection)));

    out_info.hr = p_reflection->GetDesc(&out_info.shader_desc);
    if (FAILED(out_info.hr))
        {
            LOG_ERROR("Get Shader_desc failed!");
            return;
        }
    CreatePSOInputLayout(out_info.shader_desc, out_info.pso_layout, p_reflection.Get());

    return;
}

void DXCCompiler::SaveByteCode(const wchar_t* shader_path, const wchar_t* pdb_path) const
{
    ENGINE_ASSERT(SUCCEEDED(result.hr), "Compile failed or not compile yet");
    if (shader_path != nullptr)
        {
            if (result.p_shader_bytecode.pShaderBytecode != nullptr && result.p_shader_bytecode.BytecodeLength > 0)
                {
                    FILE* fp = nullptr;
                    _wfopen_s(&fp, shader_path, L"wb");
                    fwrite(result.p_shader_bytecode.pShaderBytecode, result.p_shader_bytecode.BytecodeLength, 1, fp);
                    fclose(fp);
                }
        }
    else
        {
            LOG_ERROR("got empty shader path!");
        }

    if (pdb_path != nullptr)
        {
            if (result.p_shader_pdb.pShaderBytecode != nullptr && result.p_shader_pdb.BytecodeLength > 0)
                {
                    FILE* fp = nullptr;

                    _wfopen_s(&fp, result.pdb_name.c_str(), L"wb");
                    fwrite(result.p_shader_pdb.pShaderBytecode, result.p_shader_pdb.BytecodeLength, 1, fp);
                    fclose(fp);
                }
        }
    else
        {
            LOG_ERROR("got empty shader path!");
        }
}

void DXCCompiler::SaveByteCode() const { SaveByteCode(result.shader_name.c_str(), result.pdb_name.c_str()); }