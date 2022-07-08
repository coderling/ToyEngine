#pragma once
#include "IDXCCompiler.hpp"
#include "LoadDLL.hpp"

namespace Toy::Graphics
{
struct ID3D12Factory
{
   public:
    virtual void CreateDXCCompiler(IDXCCompiler** pp_compiler) = 0;
};

}  // namespace Toy::Graphics

#if ENGINE_DLL_EXPORT
typedef Toy::Graphics::ID3D12Factory* (*GetD3D12FactoryType)();
inline GetD3D12FactoryType LoadGraphicsD3D12()
{
    return (GetD3D12FactoryType)(Toy::Engine::LoadDLL("RenderDeviceD3D12", "GetD3D12Factory"));
}
#else
#endif
Toy::Graphics::ID3D12Factory* GetD3D12Factory();
