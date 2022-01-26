#include "App.hpp"

using namespace Toy::Engine;

bool App::quit = false;

App::App(const AppArgs& args)
{
	this->args = args;
}

int App::Initialize()
{
	int ret = CreateAppWindow();
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
