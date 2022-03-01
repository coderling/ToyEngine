#include "Pipeline.hpp"
#include "IApp.hpp"
#include "GlobalEnvironment.hpp"

using namespace Toy::Graphics;

std::unique_ptr<IPipeline> pipeline;

IPipeline* IPipeline::GetInstance()
{
	if (pipeline == nullptr)
	{
		pipeline = std::make_unique<Pipeline>();
	}

	return pipeline.get();
}

int Pipeline::Initialize() 
{
	return 0;
}

void Pipeline::Finalize()
{

}

void Pipeline::Tick()
{
	BeforeRender();
	Render();
	for (auto it = custom_render_funcs.begin(); it != custom_render_funcs.end();)
	{
		auto fg = *it;
		auto handler = fg->GetHandler();

		if (fg->GetState() > 0)
		{
			if (nullptr != handler)
			{
				handler->Render();
			}
		}

		if (fg->GetState() < 0)
		{
			it = custom_render_funcs.erase(it);
			if (nullptr != handler)
			{
				handler->Unload();
			}
		}
		else
		{
			++it;
		}
	}
	AfterRender();
	Toy::Engine::IApp::env->GetGraphics()->GetSwapChain()->Present();
}

void Pipeline::AddPipelineFragment(PipelineFragment* fg)
{
	if (!custom_render_funcs.contains(fg))
	{
		custom_render_funcs.emplace(fg);
		auto handler = fg->GetHandler();
		if (nullptr != handler)
		{
			handler->Load();
		}
		fg->Resume();
	}
}

void Pipeline::Render()
{

}

void Pipeline::BeforeRender()
{

}

void Pipeline::AfterRender()
{

}
