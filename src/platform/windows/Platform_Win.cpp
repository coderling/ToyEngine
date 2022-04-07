#include "../Platform.hpp"
#include "WinApp.hpp"
#include <memory>

std::unique_ptr<IApp> p_app;


int Toy::Platform::InitEngine(const std::string & title)
{
	const AppArgs args(title);
	return InitEngine(args);
}
int Toy::Platform::InitEngine(const Toy::Engine::AppArgs& args)
{
	p_app = std::make_unique<WinApp>(args);
	const int& ret = p_app->Initialize();
	return ret;
}

int Toy::Platform::StartEngine()
{
	if (p_app == nullptr)
	{
		return -1;
	}

	while (!p_app->IsQuit())
	{
		p_app->Tick();
	}

	p_app->Destroy();
	return 0;
}