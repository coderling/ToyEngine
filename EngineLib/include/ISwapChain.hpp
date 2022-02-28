#pragma once

#include "IObject.hpp"

#include <cstdint>

namespace Toy::Graphics
{
	class ISwapChain : public Toy::Engine::IObject, public Toy::Engine::NoCopy
	{
	public:
		virtual void Present() = 0 ;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual bool IsFullScreen() const noexcept = 0;
		virtual void SetFullScreen(bool state) = 0;
	};
}