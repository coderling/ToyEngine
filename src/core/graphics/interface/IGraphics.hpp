#pragma once

#include "../../interface/ISystem.hpp"
#include "../GraphicsDef.hpp"
#include "ISwapChain.hpp"
#include "IGraphicsCommandQueue.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
	class IGraphics :public  ISystem
	{
	public:
		virtual IDevice* GetDevice() const noexcept = 0;
		virtual ISwapChain* GetSwapChain() const noexcept = 0;
		virtual IGraphicsCommandQueue* GetCommandQueue() = 0;
		static std::unique_ptr<IGraphics> Create();
	};
}