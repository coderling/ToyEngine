#include "App.hpp"

using namespace Toy::Engine;
using namespace Toy::Graphics;

bool App::quit = false;
GlobalEnvironment _env{};
GlobalEnvironment* const IApp::env = &_env;

App::App(const AppArgs& args):IApp(args)
{
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

void App::Destroy() {
	Finalize();
}

int App::CreateAppWindow() { return 0; }

int App::InitGraphics() { return 0; }
