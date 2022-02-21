#pragma once

#include "ISystem.hpp"
#include "Def.hpp"

namespace Toy::Engine
{
	class IBaseScene : public ISystem, public NoCopy
	{
	};
}