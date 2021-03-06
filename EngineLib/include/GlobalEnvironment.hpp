#pragma once

#include <memory>
#include "IGraphics.hpp"
#include "IPipeline.hpp"
#include "pch.hpp"

namespace Toy::Engine
{
	class IApp;
	class App;
	struct TOY_LIB_API  GlobalEnvironment
	{
		friend App;
	public:
		IApp* GetApp() const noexcept { return app; }
		Toy::Graphics::IGraphics* GetGraphics() const noexcept { return graphics; }
		Toy::Graphics::IPipeline* GetPipeline() const	noexcept { return pipeline; }
	private:
		IApp* app = nullptr;
		Toy::Graphics::IGraphics* graphics = nullptr;
		Toy::Graphics::IPipeline* pipeline = nullptr;
	};
}
