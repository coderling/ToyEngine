#include "PipelineFragment.hpp"

using namespace Toy::Graphics;

PipelineFragment::PipelineFragment(PIPELINE_STAGE stage): stage(stage), running(0), handler(nullptr)
{
}

void PipelineFragment::Stop()
{
	running = 0;
}

void PipelineFragment::Resume()
{
	running = 1;
}

void PipelineFragment::End()
{
	running = -1;
}

int PipelineFragment::GetState() const noexcept
{
	return running;
}

PIPELINE_STAGE PipelineFragment::GetStage() const noexcept
{
	return stage;
}

void PipelineFragment::Init(IPipelineFragmentHandler* handler)
{
	this->handler = handler;
}

IPipelineFragmentHandler* PipelineFragment::GetHandler() const noexcept
{
	return handler;
}
