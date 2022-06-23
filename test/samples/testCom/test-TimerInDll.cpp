

#include <stdio.h>
#include "ID3D12Factory.hpp"
#include "IDXCCompiler.hpp"

int main()
{
    wchar_t* cwd;
    cwd = (wchar_t*)malloc(FILENAME_MAX * sizeof(wchar_t));
    _wgetcwd(cwd, FILENAME_MAX);
    auto GetFactoryFunc = LoadGraphicsD3D12();
    auto p_factory = GetFactoryFunc();
    Toy::Graphics::IDXCCompiler* p_compiler = nullptr;
    p_factory->CreateDXCCompiler(&p_compiler);
    Toy::Graphics::ICompileArgs* p_args =
        p_compiler->GetArgsHandle(L"I:/GraphicsLearn/ToyEngine/assets/builtin_shaders/shaders/color.hlsl");
    p_args->SetEntry(L"VS_Main");
    p_args->SetShaderModel(L"vs_6_1");
    p_args->AddInlucdePath(L"I:\\GraphicsLearn\\ToyEngine\\assets\\builtin_shaders\\inc");
    p_args->EnableDebug();
    p_args->SetOutput(L"I:/GraphicsLearn/ToyEngine/assets/builtin_shaders/shaders/color.vs1.cso");
    p_args->EnablePDB(L"I:/GraphicsLearn/ToyEngine/assets/builtin_shaders/shaders/color.vs1.pdb");
    p_compiler->Compile();
    p_compiler->SaveByteCode();
    return 0;
}