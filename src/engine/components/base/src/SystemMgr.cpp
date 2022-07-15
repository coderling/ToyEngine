#include "SystemMgr.hpp"
#include "GlobalEnvironment.hpp"
#include "IPipeline.hpp"
#include "IRenderDevice.hpp"
#include "ISystem.hpp"

using namespace Toy::Engine;

int SystemMgr::Initialize() { return 0; }

void SystemMgr::Tick()
{
    for (auto& sys : systems)
        {
            sys.second->Tick();
        }
}

void SystemMgr::Finalize() { systems.clear(); }
