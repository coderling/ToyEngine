#pragma once

#include <memory>

namespace Toy::Graphics
{
	class IGraphics;
}

namespace Toy::Engine
{
	class IApp;
	struct GlobalEnvironment
	{
		IApp* app = nullptr;
		std::unique_ptr<Toy::Graphics::IGraphics> graphics = nullptr;
	};
}
