#include "PipelineFragment.hpp"

using namespace Toy::Graphics;

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

void PipelineFragment::Init(IPipelineFragmentHandler* handler)
{
	this->handler = handler;
}

IPipelineFragmentHandler* PipelineFragment::GetHandler() const noexcept
{
	return handler;
}
