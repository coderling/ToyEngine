#pragma once

#include "ISystem.hpp"
#include "Def.hpp"
#include "GraphicsDef.hpp"
#include "ISwapChain.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
	class IGraphics :public  ISystem, public Toy::NoCopy
	{
	public:
		int Initialize() override;
		virtual IDevice* GetDevice() const noexcept = 0;
		virtual ISwapChain* GetSwapChain() const noexcept = 0;
	};
}