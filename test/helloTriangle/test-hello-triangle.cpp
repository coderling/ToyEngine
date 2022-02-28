#include <iostream>

#include "RenderLogic.hpp"
#include <PipelineFragment.hpp>
#include <IApp.hpp>
#include <Platform.hpp>
#include <GlobalEnvironment.hpp>
#include <IPipeline.hpp>

using namespace std;

int main(int argc, char** argv)
{
    Toy::Platform::InitEngine(L"HelloTriangle");
    std::unique_ptr<Toy::Graphics::PipelineFragment> fg = std::make_unique<Toy::Graphics::PipelineFragment>();
    auto logic = std::make_unique<RenderLogic>();
    fg->Init(logic.get());
    Toy::Engine::IApp::env->GetPipeline()->AddPipelineFragment(fg.get());
    Toy::Platform::StartEngine();
    
    return 0;
}