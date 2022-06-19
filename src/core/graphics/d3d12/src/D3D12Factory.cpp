#include "DXCCompiler.hpp"
#include "ID3D12Factory.hpp"

namespace Toy::Graphics
{
class D3D12Factory final : public ID3D12Factory
{
   public:
    static D3D12Factory* GetInstance()
    {
        static D3D12Factory factory;
        return &factory;
    }

    void CreateDXCCompiler(IDXCCompiler** pp_compiler) override
    {
        DXCCompiler* p_compiler = new DXCCompiler();
        *pp_compiler = p_compiler;
    }
};
}  // namespace Toy::Graphics
Toy::Graphics::ID3D12Factory* GetD3D12Factory() { return Toy::Graphics::D3D12Factory::GetInstance(); }
