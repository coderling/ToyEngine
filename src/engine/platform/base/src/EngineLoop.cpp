#include "EngineLoop.hpp"
#include "Logger.hpp"
#include "SystemMgr.hpp"

namespace Toy::Platform
{
EngineLoop::EngineLoop(std::unique_ptr<Engine::IClient> _client) : client(std::move(_client)), system_mgr(nullptr) {}

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

int EngineLoop::SystemSetup()
{
    system_mgr = std::make_unique<Engine::SystemMgr>();
    auto ret = system_mgr->Initialize();

    return ret;
}

}  // namespace Toy::Platform