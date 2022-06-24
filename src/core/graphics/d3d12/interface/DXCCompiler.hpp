#pragma once
#include <inc/d3d12shader.h>
#include <inc/dxcapi.h>
#include <wrl/client.h>
#include <vector>
#include "CStringTool.hpp"
#include "DXCCompileArgs.hpp"
#include "DebugUtility.hpp"
#include "ShaderInfos.hpp"
#include "TObject.hpp"

using namespace Microsoft::WRL;
namespace Toy::Graphics
{
class DXCCompiler final : public Engine::TObject<IDXCCompiler>
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
    struct ShaderReflectInfo
    {
        HRESULT hr;
        D3D12_SHADER_DESC shader_desc;

        ShaderPSOInputLayout pso_layout;

       public:
        ShaderReflectInfo() noexcept : hr{S_FALSE}, shader_desc{} {}
    };

   private:
    std::unique_ptr<DXCCompileArgs> p_args = nullptr;

    using TBase = Toy::Engine::TObject<IDXCCompiler>;

    IMPLEMENT_CONSTRUCT_STATEMENT(DXCCompiler);

   public:
    IMPLEMENT_QUERYINTERFACE_STATEMENT();
    void OnDestroy() override;
    ICompileArgs* GetArgsHandle(const wchar_t* path) override;
    void Compile(Engine::IDataBlob** pp_shader_bytecode, Engine::IDataBlob** pp_shader_pdb, TOY_RESULT& tr) override;
};
}  // namespace Toy::Graphics