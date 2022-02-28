#pragma once
#include "ISystem.hpp"
#include <vector>
#include <memory>
#include <unordered_set>

namespace Toy::Engine
{
	class SystemMgr final: public ISystem 
	{
	public:
		int Initialize() override;
		void Tick() override;

		void RegisterSystem(ISystem* sys);
		void UnRegisterSystem(ISystem* sys);
	private:
		void Finalize() override;
		
		std::unordered_set<ISystem*> systems;
	};
}