#pragma once
#include <inc/d3d12shader.h>
#include <inc/dxcapi.h>
#include <wrl/client.h>
#include "IDXCCompiler.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
struct DXCCompileArgs : public ICompileArgs
{
   private:
    friend class DXCCompiler;
    const wchar_t* file_path;
    ComPtr<IDxcCompilerArgs> p_args;

    const char* source;
    std::size_t source_length;

   public:
    DXCCompileArgs(const wchar_t* path) noexcept : file_path(path), p_args(nullptr), source(nullptr), source_length(0)
    {
        DxcCreateInstance(CLSID_DxcCompilerArgs, IID_PPV_ARGS(&p_args));
        // ENGINE_ASSERT(p_args != NULL, "IDxcCompilerArgs create failed");
    }

    ~DXCCompileArgs() {}

    void SetSource(const char* p_source, const std::size_t& _source_length) { source = p_source, source_length = _source_length; }

    void SetEntry(LPCWSTR arg) override
    {
        static LPCWSTR entry_opt[2] = {L"-E", arg};
        p_args->AddArguments(entry_opt, 2);
    }

    void AddInlucdePath(LPCWSTR inc) override
    {
        static LPCWSTR argv[2] = {L"-I", inc};
        p_args->AddArguments(argv, 2);
    }

    void EnableDebug() override
    {
        static LPCWSTR argv[1] = {L"-Zi"};
        p_args->AddArguments(argv, 1);
    }

    void SetOutput(LPCWSTR out_path) override
    {
        static LPCWSTR argv[2] = {L"-Fo", out_path};
        p_args->AddArguments(argv, 2);
    }

    void EnablePDB(LPCWSTR path_pdb) override
    {
        static LPCWSTR argv[2] = {L"-Fd", path_pdb};
        p_args->AddArguments(argv, 2);
    }

    void SetShaderModel(LPCWSTR sm) override
    {
        static LPCWSTR argv[2] = {L"-T", sm};
        p_args->AddArguments(argv, 2);
    }

    void AddMacro(LPCWSTR macro) override
    {
        static LPCWSTR argv[2] = {L"-D", macro};
        p_args->AddArguments(argv, 2);
    }

    void AddCustomArgs(LPCWSTR* argv, const UINT32& argc) override { p_args->AddArguments(argv, argc); }

    void Clear() override
    {
        p_args.Reset();
        DxcCreateInstance(CLSID_DxcCompilerArgs, IID_PPV_ARGS(&p_args));
    }

    void Assign(const void* source, const std::size_t& source_length) override
    {
        this->source = reinterpret_cast<const char*>(source);
        this->source_length = source_length;
    }

    LPCWSTR* GetArguments() const noexcept { return p_args->GetArguments(); }

    UINT32 GetArgCount() const noexcept { return p_args->GetCount(); }
};
}  // namespace Toy::Graphics