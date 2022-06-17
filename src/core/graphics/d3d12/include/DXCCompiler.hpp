#pragma once
#include <inc/d3d12shader.h>
#include <inc/dxcapi.h>
#include <wrl/client.h>
#include <vector>
#include "CStringTool.hpp"
#include "DebugUtility.hpp"
#include "ShaderInfos.hpp"

using namespace Microsoft::WRL;
namespace Toy::Graphics
{
class DXCCompiler final
{
   public:
// copy from DxilContainer.h
#define DXIL_FOURCC(ch0, ch1, ch2, ch3)                                                                                                    \
    ((uint32_t)(uint8_t)(ch0) | (uint32_t)(uint8_t)(ch1) << 8 | (uint32_t)(uint8_t)(ch2) << 16 | (uint32_t)(uint8_t)(ch3) << 24)

    enum DxilFourCC
    {
        DFCC_Container = DXIL_FOURCC('D', 'X', 'B', 'C'),  // for back-compat with tools that look for DXBC containers
        DFCC_ResourceDef = DXIL_FOURCC('R', 'D', 'E', 'F'),
        DFCC_InputSignature = DXIL_FOURCC('I', 'S', 'G', '1'),
        DFCC_OutputSignature = DXIL_FOURCC('O', 'S', 'G', '1'),
        DFCC_PatchConstantSignature = DXIL_FOURCC('P', 'S', 'G', '1'),
        DFCC_ShaderStatistics = DXIL_FOURCC('S', 'T', 'A', 'T'),
        DFCC_ShaderDebugInfoDXIL = DXIL_FOURCC('I', 'L', 'D', 'B'),
        DFCC_ShaderDebugName = DXIL_FOURCC('I', 'L', 'D', 'N'),
        DFCC_FeatureInfo = DXIL_FOURCC('S', 'F', 'I', '0'),
        DFCC_PrivateData = DXIL_FOURCC('P', 'R', 'I', 'V'),
        DFCC_RootSignature = DXIL_FOURCC('R', 'T', 'S', '0'),
        DFCC_DXIL = DXIL_FOURCC('D', 'X', 'I', 'L'),
        DFCC_PipelineStateValidation = DXIL_FOURCC('P', 'S', 'V', '0'),
        DFCC_RuntimeData = DXIL_FOURCC('R', 'D', 'A', 'T'),
        DFCC_ShaderHash = DXIL_FOURCC('H', 'A', 'S', 'H'),
        DFCC_ShaderSourceInfo = DXIL_FOURCC('S', 'R', 'C', 'I'),
        DFCC_CompilerVersion = DXIL_FOURCC('V', 'E', 'R', 'S'),
    };
#undef DXIL_FOURCC
    // end copy DxilContainer.h
    struct CompileResult
    {
       private:
        friend DXCCompiler;
        HRESULT hr;
        std::wstring shader_name;
        D3D12_SHADER_BYTECODE p_shader_bytecode;
        std::wstring pdb_name;
        D3D12_SHADER_BYTECODE p_shader_pdb;

       private:
        void* CopyBytecode(void* bytecode_data, const std::size_t& byte_length) const
        {
            auto bytedata = new uint8_t[byte_length];
            memcpy_s(bytedata, byte_length, bytecode_data, byte_length);
            return bytedata;
        }

        void SetShaderCode(IDxcBlob* blob, IDxcBlobUtf16* utf16_shader_name)
        {
            if (utf16_shader_name != nullptr)
                {
                    shader_name = std::wstring(utf16_shader_name->GetStringPointer(), utf16_shader_name->GetStringLength());
                }

            if (blob != nullptr)
                {
                    p_shader_bytecode.pShaderBytecode = CopyBytecode(blob->GetBufferPointer(), blob->GetBufferSize());
                    p_shader_bytecode.BytecodeLength = blob->GetBufferSize();
                }
        }

        void SetPDBCode(IDxcBlob* blob, IDxcBlobUtf16* utf16_pdb_name)
        {
            if (utf16_pdb_name != nullptr)
                {
                    pdb_name = std::wstring(utf16_pdb_name->GetStringPointer(), utf16_pdb_name->GetStringLength());
                }

            if (blob != nullptr)
                {
                    p_shader_pdb.pShaderBytecode = CopyBytecode(blob->GetBufferPointer(), blob->GetBufferSize());
                    p_shader_pdb.BytecodeLength = blob->GetBufferSize();
                }
        }

       public:
        CompileResult() noexcept : hr(S_FALSE), shader_name{}, p_shader_bytecode{nullptr}, pdb_name{}, p_shader_pdb{nullptr} {}
        ~CompileResult()
        {
            if (p_shader_bytecode.pShaderBytecode != nullptr)
                {
                    delete[] static_cast<const uint8_t*>(p_shader_bytecode.pShaderBytecode);
                    p_shader_bytecode.pShaderBytecode = nullptr;
                    p_shader_bytecode.BytecodeLength = 0;
                }

            if (p_shader_pdb.pShaderBytecode != nullptr)
                {
                    delete[] static_cast<const uint8_t*>(p_shader_pdb.pShaderBytecode);
                    p_shader_bytecode.pShaderBytecode = nullptr;
                    p_shader_bytecode.BytecodeLength = 0;
                }
        }

        const D3D12_SHADER_BYTECODE& GetShaderByteCode() const noexcept { return p_shader_bytecode; }
        const D3D12_SHADER_BYTECODE& GetPDBByteCode() const noexcept { return p_shader_pdb; }
        bool IsComplied() const noexcept { return SUCCEEDED(hr); }
    };

    struct ShaderReflectInfo
    {
        HRESULT hr;
        D3D12_SHADER_DESC shader_desc;

        ShaderPSOInputLayout pso_layout;

       public:
        ShaderReflectInfo() noexcept : hr{S_FALSE}, shader_desc{} {}
    };

    struct DXCCompileArgs
    {
       private:
        friend class DXCCompiler;
        const char* file_path;
        ComPtr<IDxcCompilerArgs> p_args;

       public:
        DXCCompileArgs(const char* path) noexcept : file_path(path), p_args(nullptr)
        {
            DxcCreateInstance(CLSID_DxcCompilerArgs, IID_PPV_ARGS(&p_args));
            ENGINE_ASSERT(p_args != NULL, "IDxcCompilerArgs create failed");
        }
        ~DXCCompileArgs() {}

        DXCCompileArgs& SetEntry(LPCWSTR arg)
        {
            static LPCWSTR entry_opt[2] = {L"-E", arg};
            p_args->AddArguments(entry_opt, 2);
            return *this;
        }

        DXCCompileArgs& AddInlucdePath(LPCWSTR inc)
        {
            static LPCWSTR argv[2] = {L"-I", inc};
            p_args->AddArguments(argv, 2);
            return *this;
        }

        DXCCompileArgs& EnableDebug()
        {
            static LPCWSTR argv[1] = {L"-Zi"};
            p_args->AddArguments(argv, 1);
            return *this;
        }

        DXCCompileArgs& SetOutput(LPCWSTR out_path)
        {
            static LPCWSTR argv[2] = {L"-Fo", out_path};
            p_args->AddArguments(argv, 2);
            return *this;
        }

        DXCCompileArgs& EnablePDB(LPCWSTR path_pdb)
        {
            static LPCWSTR argv[2] = {L"-Fd", path_pdb};
            p_args->AddArguments(argv, 2);
            return *this;
        }

        DXCCompileArgs& SetShaderModel(LPCWSTR sm)
        {
            static LPCWSTR argv[2] = {L"-T", sm};
            p_args->AddArguments(argv, 2);
            return *this;
        }
        DXCCompileArgs& AddCustomArgs(LPCWSTR* argv, const UINT32& argc)
        {
            p_args->AddArguments(argv, argc);
            return *this;
        }

        LPCWSTR* GetArguments() const { return p_args->GetArguments(); }

        UINT32 GetArgCount() const { return p_args->GetCount(); }
    };

   private:
    CompileResult result;

   public:
    void Compile(const DXCCompileArgs& args);
    void ReflectShader(const D3D12_SHADER_BYTECODE& bytecode, ShaderReflectInfo& out_info) const;
    void SaveByteCode(const wchar_t* path, const wchar_t* pdb_path) const;
    void SaveByteCode() const;

   private:
    void CreatePSOInputLayout(const D3D12_SHADER_DESC& shader_desc, ShaderPSOInputLayout& layout,
                              ID3D12ShaderReflection* p_reflection) const;
};
}  // namespace Toy::Graphics