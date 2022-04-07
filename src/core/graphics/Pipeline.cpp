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
	AfterRender();
	FinishFrame();
}

void Pipeline::FinishFrame()
{
	auto graphics = Toy::Engine::IApp::env->GetGraphics();
	graphics->GetSwapChain()->Present();
	graphics->WaitForGpu();
}

std::unordered_set<PipelineFragment*>& Pipeline::GetFuncs(const PIPELINE_STAGE& st) noexcept
{
	switch (st)
	{
	case PIPELINE_STAGE::BEFORE_RENDER:
	{
		return custom_render_funcs_before;
	}
	break;
	case PIPELINE_STAGE::AFTER_RENDER:
	{
		return custom_render_funcs_after;
	}
	break;
	default:
	{
		return custom_render_funcs;
	}
	break;
	}
}

void Pipeline::AddPipelineFragment(PipelineFragment* fg)
{
	auto& funcs = GetFuncs(fg->GetStage());
	if (!funcs.contains(fg))
	{
		funcs.emplace(fg);
		auto handler = fg->GetHandler();
		if (nullptr != handler)
		{
			handler->Load();
		}
		fg->Resume();
	}
}

void Pipeline::ExecuteFuncs(const PIPELINE_STAGE& st) 
{
	auto& funcs = GetFuncs(st);
	for (auto it = funcs.begin(); it != funcs.end();)
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
			it = funcs.erase(it);
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
}

void Pipeline::Render()
{
	ExecuteFuncs(PIPELINE_STAGE::ONRENDER);
}

void Pipeline::BeforeRender()
{
	ExecuteFuncs(PIPELINE_STAGE::BEFORE_RENDER);
}

void Pipeline::AfterRender()
{
	ExecuteFuncs(PIPELINE_STAGE::AFTER_RENDER);
}
