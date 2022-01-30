#pragma once

#include "Def.hpp"
#include "IObject.hpp"

#include <cstdint>

namespace Toy::Graphics
{
	class ISwapChain : public Toy::Engine::IObject, public Toy::NoCopy
	{
	public:
		virtual void Present() = 0;
		virtual void Resize(uint32_t width, uint32_t height);
		virtual bool IsFullScreen() const noexcept = 0;
	};
}