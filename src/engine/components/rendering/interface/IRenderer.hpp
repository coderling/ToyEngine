#pragma once
#include "IObject.hpp"
#include "IMaterial.hpp"
#include "IMesh.hpp"

namespace Toy::Engine::Rendering
{
class IRenderer : public IObject
{
   public:
    INTERFACEUUID(IRenderer) = {/* f6d018c7-a9a6-490e-84cf-a385295c160e */
                                0xf6d018c7,
                                0xa9a6,
                                0x490e,
                                {0x84, 0xcf, 0xa3, 0x85, 0x29, 0x5c, 0x16, 0x0e}};

    virtual IMaterial* GetMaterial() const noexcept = 0;
    virtual IMesh* GetMesh() const noexcept = 0;
};
}  // namespace Toy::Engine::Rendering