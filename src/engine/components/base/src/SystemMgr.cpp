#include "SystemMgr.hpp"
#include "GlobalEnvironment.hpp"
#include "IGraphics.hpp"
#include "IPipeline.hpp"
#include "ISystem.hpp"

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
            sys.second->Tick();
        }
}

void SystemMgr::Finalize() { systems.clear(); }
