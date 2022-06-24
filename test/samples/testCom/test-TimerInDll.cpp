

#include <stdio.h>
#include <iostream>
#include "DataBlob.hpp"
#include "ID3D12Factory.hpp"
#include "IDXCCompiler.hpp"
#include "RefCountPtr.hpp"

int main()
{
    wchar_t* cwd;
    cwd = (wchar_t*)malloc(FILENAME_MAX * sizeof(wchar_t));
    _wgetcwd(cwd, FILENAME_MAX);
    auto GetFactoryFunc = LoadGraphicsD3D12();
    auto p_factory = GetFactoryFunc();
    Toy::Graphics::IDXCCompiler* p_compiler = nullptr;
    p_factory->CreateDXCCompiler(&p_compiler);
    Toy::Graphics::ICompileArgs* p_args = p_compiler->GetArgsHandle(L"E:/GitProj/ToyEngine/assets/builtin_shaders/shaders/color.hlsl");
    p_args->SetEntry(L"VS_Main");
    p_args->SetShaderModel(L"vs_6_1");
    p_args->AddInlucdePath(L"E:\\GitProj\\ToyEngine\\assets\\builtin_shaders\\inc");
    p_args->EnableDebug();
    p_args->SetOutput(L"E:/GitProj/ToyEngine/assets/builtin_shaders/shaders/color.vs1.cso");
    p_args->EnablePDB(L"E:/GitProj/ToyEngine/assets/builtin_shaders/shaders/color.vs1.pdb");
    p_compiler->Compile();

    Toy::Engine::RefCountPtr<Toy::Engine::IDataBlob> p_blob;
    TOY_RESULT tr = TOY_RESULT::TR_ERROR;
    p_compiler->GetOutput(&p_blob, tr);
    auto size = p_blob->GetDataSize();
    std::cout << " strong ref blog: " << size << " RE:" << tr << std::endl;
    return 0;
}