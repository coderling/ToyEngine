#pragma once

#include <memory>

#include "../graphics/interface/IGraphics.hpp"

namespace Toy::Engine
{
	class IApp;
	class App;
	struct GlobalEnvironment
	{
		friend App;
	public:
		IApp* GetApp() const noexcept { return app; }
		Toy::Graphics::IGraphics* GetGraphics() const noexcept { return graphics.get(); }
	private:
		IApp* app = nullptr;
		std::unique_ptr<Toy::Graphics::IGraphics> graphics = nullptr;
	};
}
