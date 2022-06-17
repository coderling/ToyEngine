#include <iostream>

#include <GlobalEnvironment.hpp>
#include <IApp.hpp>
#include <IPipeline.hpp>
#include <PipelineFragment.hpp>
#include <Platform.hpp>
#include <Time.hpp>
#include "RenderLogic.hpp"

using namespace std;

int main(int argc, char** argv)
{
    auto timer = Toy::Engine::Timer();
    auto now = timer.ElapsedTimef();
    while (false)
        // while (timer.ElapsedTimef() - now < 10)
        {
        }
    Toy::Engine::AppArgs args("HelloTriangle");
    args.ParseCommandArgs(argc, argv);
    Toy::Platform::InitEngine(args);
    std::unique_ptr<Toy::Graphics::PipelineFragment> fg =
        std::make_unique<Toy::Graphics::PipelineFragment>(Toy::Graphics::PIPELINE_STAGE::ONRENDER);
    auto logic = std::make_unique<RenderLogic>();
    fg->Init(logic.get());
    Toy::Engine::IApp::env->GetPipeline()->AddPipelineFragment(fg.get());
    Toy::Platform::StartEngine();

    return 0;
}