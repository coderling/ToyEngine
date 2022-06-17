#include "SystemMgr.hpp"
#include "GlobalEnvironment.hpp"
#include "IGraphics.hpp"
#include "IPipeline.hpp"

using namespace Toy::Engine;

int SystemMgr::Initialize()
{
    // setup pipeline
    GlobalEnvironment::GetEnv().pipeline = Graphics::IPipeline::GetInstance();
    GlobalEnvironment::GetEnv().graphics = Graphics::IGraphics::GetInstance();

    return 0;
}

void SystemMgr::Tick()
{
    for (auto& sys : systems)
        {
            sys->Tick();
        }
}

void SystemMgr::Finalize()
{
    for (auto& sys : systems)
        {
            sys->Destroy();
        }

    systems.clear();
}

void SystemMgr::RegisterSystem(ISystem* sys)
{
    if (!systems.contains(sys))
        {
            systems.emplace(sys);
        }
}

void SystemMgr::UnRegisterSystem(ISystem* sys)
{
    const auto& it = systems.find(sys);
    if (it != systems.end())
        {
            systems.erase(it);
        }
}
