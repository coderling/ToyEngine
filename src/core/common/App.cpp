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

	ret = SystemSetup();
	if (ret != 0)
	{
		Quit();
		return ret;
	}

	return 0;
}

void App::Finalize()
{
	system_mgr->Destroy();
}

void App::Tick()
{
	system_mgr->Tick();
}

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

int App::CreateAppWindow() { return 0; }

int App::SystemSetup()
{
	system_mgr = std::make_unique<SystemMgr>();
	system_mgr->Initialize();
	IApp::env->graphics = Toy::Graphics::IGraphics::GetInstance();
	int ret = IApp::env->graphics->Initialize();
	if (ret != 0)
		return ret;
	
	IApp::env->pipeline = Toy::Graphics::IPipeline::GetInstance();
	ret = IApp::env->pipeline->Initialize();
	system_mgr->RegisterSystem(IApp::env->pipeline);

	return ret;
}
