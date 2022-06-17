#pragma once
#include <memory>
#include "Client.hpp"
#include "ISystem.hpp"

namespace Toy::Platform
{
class EngineLoop : public Engine::ISystem
{
    std::unique_ptr<Engine::IClient> client;
    std::unique_ptr<Engine::ISystem> system_mgr;

   public:
    explicit EngineLoop(std::unique_ptr<Engine::IClient> _client);

    ~EngineLoop() noexcept override;
    int Initialize() override;
    void Tick() override;

   private:
    void Finalize() override;
    int SystemSetup();
};
}  // namespace Toy::Platform