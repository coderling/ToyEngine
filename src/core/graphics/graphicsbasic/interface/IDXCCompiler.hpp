#pragma once
#include <cstdint>
#include "IDataBlob.hpp"
#include "RefCountPtr.hpp"

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

    virtual void AddMacro(const wchar_t* macro) = 0;

    virtual void AddCustomArgs(const wchar_t** argv, const std::uint32_t& argc) = 0;

    virtual void Assign(const void* source, const std::size_t& source_length) = 0;

    virtual void Clear() = 0;
};

class IDXCCompiler : public Toy::IObject
{
   public:
    INTERFACEUUID(IDXCCompiler) = {/* 3f7fdf04-0208-43b3-8428-dbe1cbbbb36b */
                                   0x3f7fdf04,
                                   0x0208,
                                   0x43b3,
                                   {0x84, 0x28, 0xdb, 0xe1, 0xcb, 0xbb, 0xb3, 0x6b}};

    virtual ICompileArgs* GetArgsHandle(const wchar_t* path) = 0;
    virtual void Compile(Engine::IDataBlob** pp_shader_bytecode, Engine::IDataBlob** pp_shader_pdb, TOY_RESULT& tr) = 0;
};
}  // namespace Toy::Graphics