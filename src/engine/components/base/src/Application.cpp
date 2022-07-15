#include "Application.hpp"
#include "GlobalEnvironment.hpp"
#include "Logger.hpp"
#include "SystemMgr.hpp"

namespace Toy::Platform
{
Application::Application(std::unique_ptr<Engine::IClient> _client)
    : client(std::move(_client)),
      system_mgr(nullptr)
{
    Engine::GlobalEnvironment::GetEnv().init_args = &_client->GetArgs();
    Engine::GlobalEnvironment::GetEnv().hwnd = _client->GetHwnd();
}

Application::~Application() noexcept { LOG_INFO("~Application()"); }

int Application::Initialize()
{
    auto ret = GraphicsSetUp();
    if (ret != 0)
        {
            return ret;
        }

    ret = SystemSetup();
    if (ret != 0)
        {
            client->Quit();
            return ret;
        }

    return ret;
}

void Application::Tick()
{
    while (!client->IsQuit())
        {
            client->Tick();
            system_mgr->Tick();
        }
}

void Application::Finalize() { system_mgr->Destroy(); }

int Application::SystemSetup() { return Engine::SystemMgr::Instance().Initialize(); }

int Application::GraphicsSetUp() { return 0; }
}  // namespace Toy::Platform