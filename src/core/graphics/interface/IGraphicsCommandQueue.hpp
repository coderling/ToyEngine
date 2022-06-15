#pragma once

#include <array>
#include <cstdint>
#include "GraphicsDef.hpp"
#include "IGraphicsCommandList.hpp"
#include "IObject.hpp"

namespace Toy::Graphics
{

class IGraphicsCommandQueue : public Toy::Engine::IObject, public Toy::Engine::NoCopy
{
   public:
};
}  // namespace Toy::Graphics
