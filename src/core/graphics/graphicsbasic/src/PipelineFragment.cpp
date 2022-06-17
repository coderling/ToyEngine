#include "PipelineFragment.hpp"
#include <DebugUtility.hpp>

using namespace Toy::Graphics;

PipelineFragment::PipelineFragment() : running(ERUNNING_STATE::RS_IDLE), handler(nullptr) {}

void PipelineFragment::Stop()
{
    ENGINE_ASSERT_EXPR(running != ERUNNING_STATE::RS_END);
    running = ERUNNING_STATE::RS_IDLE;
}

void PipelineFragment::Resume()
{
    ENGINE_DEV_CHECK_EXPR(running == ERUNNING_STATE::RS_IDLE);
    running = ERUNNING_STATE::RS_RUNNING;
}

void PipelineFragment::End() { running = ERUNNING_STATE::RS_END; }

bool PipelineFragment::IsIdle() const noexcept { return running == ERUNNING_STATE::RS_IDLE; }
bool PipelineFragment::IsRuning() const noexcept { return running == ERUNNING_STATE::RS_RUNNING; }
bool PipelineFragment::IsDead() const noexcept { return running == ERUNNING_STATE::RS_END; }

void PipelineFragment::Init(std::unique_ptr<IPipelineFragmentHandler> handler) { this->handler = std::move(handler); }

IPipelineFragmentHandler* PipelineFragment::GetHandler() const noexcept { return handler.get(); }
