#include "SystemMgr.hpp"

using namespace Toy::Engine;

int SystemMgr::Initialize()
{
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
