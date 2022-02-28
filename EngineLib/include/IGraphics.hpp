#pragma once

#include "IObject.hpp"
#include "GraphicsDef.hpp"
#include "ISwapChain.hpp"
#include "IGraphicsCommandQueue.hpp"

using namespace Toy::Engine;

namespace Toy::Graphics
{
	class IGraphics :public  IObject, public NoCopy
	{
	public:
		static IGraphics* GetInstance();
		virtual int Initialize() = 0;
		virtual IDevice* GetDevice() const noexcept = 0;
		virtual ISwapChain* GetSwapChain() const noexcept = 0;
		virtual IGraphicsCommandQueue* GetCommandQueue() = 0;
	protected:
		void OnDestroy() final  override { Finalize(); }
	protected:
		virtual void Finalize() = 0;
	};
}