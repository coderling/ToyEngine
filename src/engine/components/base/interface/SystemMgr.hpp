#pragma once
#include <memory>
#include <unordered_set>
#include <vector>
#include "ISystem.hpp"

namespace Toy::Engine
{
class SystemMgr final : public ISystem
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
}  // namespace Toy::Engine