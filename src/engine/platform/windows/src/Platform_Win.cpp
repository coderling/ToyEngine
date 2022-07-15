#include <memory>
#include "Application.hpp"
#include "Platform.hpp"
#include "Windows.hpp"

std::unique_ptr<Toy::Platform::Application> p_engine;

int Toy::Platform::InitEngine(const std::string& title)
{
    const AppArgs args(title);
    return InitEngine(args);
}
int Toy::Platform::InitEngine(const Toy::Engine::AppArgs& args)
{
    auto p_client = std::make_unique<Windows>(args);
    p_engine = std::make_unique<Application>(std::move(p_client));
    const int& ret = p_engine->Initialize();
    return ret;
}

int Toy::Platform::StartEngine()
{
    if (p_engine == nullptr)
        {
            return -1;
        }

    p_engine->Tick();
    p_engine->Destroy();
    return 0;
}