#pragma once
#include <cstdint>
#include "IDataBlob.hpp"

namespace Toy::Graphics
{

struct ICompileArgs
{
    virtual void SetEntry(const wchar_t* arg) = 0;

    virtual void AddInlucdePath(const wchar_t* inc) = 0;

    virtual void EnableDebug() = 0;

    virtual void SetOutput(const wchar_t* out_path) = 0;

    virtual void EnablePDB(const wchar_t* path_pdb) = 0;

    virtual void SetShaderModel(const wchar_t* sm) = 0;

    virtual void AddCustomArgs(const wchar_t** argv, const std::uint32_t& argc) = 0;

    virtual const wchar_t** GetArguments() const = 0;

    virtual std::uint32_t GetArgCount() const = 0;
};
class IDXCCompiler
{
   public:
    virtual ICompileArgs* ApplyArgsInstance(const wchar_t* path) = 0;
    virtual void Compile(const ICompileArgs* p_args) = 0;
    virtual void SaveByteCode() const = 0;
};
}  // namespace Toy::Graphics