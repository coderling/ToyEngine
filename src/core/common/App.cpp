#include <memory>
#include "App.hpp"
#include "GlobalEnvironment.hpp"

using namespace Toy::Engine;
using namespace Toy::Graphics;

bool App::quit = false;
GlobalEnvironment _env{};
GlobalEnvironment* const IApp::env = &_env;

App::App(const AppArgs& args)
{
	this->args = std::make_unique<AppArgs>(args);
	env->app = this;
}

int App::Initialize()
{
	int ret = CreateAppWindow();
	if (ret != 0)
	{
		Quit();
		return ret;
	}

	ret = InitGraphics();
	if (ret != 0)
	{
		Quit();
		return ret;
	}

	return 0;
}

void App::Finalize(){ }

void App::Tick(){}

bool App::IsQuit() const
{
	return quit;
}

void App::Quit()
{
	quit = true;
}

const AppArgs* App::GetArgs() const noexcept
{
	return args.get();
}

void App::Destroy() {
	Finalize();
}

int App::CreateAppWindow() { return 0; }

int App::InitGraphics()
{
	IApp::env->graphics = Toy::Graphics::IGraphics::Create();
	int ret = IApp::env->graphics->Initialize();
	return ret;
}
