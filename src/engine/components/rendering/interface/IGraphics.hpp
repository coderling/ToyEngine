#pragma once
#include "IMesh.hpp"
#include "IMaterial.hpp"

namespace Toy::Engine::Rendering
{
class IGraphics : public IObject
{
   public:
    INTERFACEUUID(IGraphics) = {/* 3bbda469-6466-4683-affc-a2899db62fa0 */
                                0x3bbda469,
                                0x6466,
                                0x4683,
                                {0xaf, 0xfc, 0xa2, 0x89, 0x9d, 0xb6, 0x2f, 0xa0}};

    IGraphics() = default;
    virtual ~IGraphics() = default;

    virtual void DrawMesh(IMesh* mesh, IMaterial* material) = 0;
};
}  // namespace Toy::Engine::Rendering