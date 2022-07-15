#pragma once
#include <memory>
#include "Client.hpp"

namespace Toy::Platform
{
class Application final
{
    std::unique_ptr<Engine::IClient> client;
    std::unique_ptr<Engine::ISystem> system_mgr;

   public:
    explicit Application(std::unique_ptr<Engine::IClient> _client);

    ~Application() noexcept;
    int Initialize();
    void Tick();

   private:
    void Finalize();
    int SystemSetup();
    int GraphicsSetUp();
};
}  // namespace Toy::Platform