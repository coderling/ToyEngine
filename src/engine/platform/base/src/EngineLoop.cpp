#include "EngineLoop.hpp"
#include "GlobalEnvironment.hpp"
#include "Logger.hpp"
#include "SystemMgr.hpp"

namespace Toy::Platform
{
EngineLoop::EngineLoop(std::unique_ptr<Engine::IClient> _client) : client(std::move(_client)), system_mgr(nullptr)
{
    Engine::GlobalEnvironment::GetEnv().init_args = &_client->GetArgs();
    Engine::GlobalEnvironment::GetEnv().hwnd = _client->GetHwnd();
}

EngineLoop::~EngineLoop() noexcept { LOG_INFO("~EngineLoop()"); }

int EngineLoop::Initialize()
{
    auto ret = SystemSetup();
    if (ret != 0)
        {
            client->Quit();
            return ret;
        }

    return ret;
}

void EngineLoop::Tick()
{
    while (!client->IsQuit())
        {
            client->Tick();
            system_mgr->Tick();
        }
}

void EngineLoop::Finalize() { system_mgr->Destroy(); }

int EngineLoop::SystemSetup() { return Engine::SystemMgr::Instance().Initialize(); }

}  // namespace Toy::Platform