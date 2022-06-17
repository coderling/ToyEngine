#pragma once

#include <memory>
#include "IObject.hpp"
#include "IPipelineFragmentHandler.hpp"
#include "pch.hpp"

namespace Toy::Graphics
{
enum class PIPELINE_STAGE
{
    BEFORE_RENDER,
    ONRENDER,
    AFTER_RENDER
};

class PipelineFragment : public Toy::Engine::NoCopy
{
   private:
    enum class ERUNNING_STATE
    {
        RS_IDLE = 0,
        RS_RUNNING = 1,
        RS_END = -1
    };

   public:
    PipelineFragment();
    void Init(std::unique_ptr<IPipelineFragmentHandler> handler);
    IPipelineFragmentHandler* GetHandler() const noexcept;
    void Stop();

    void Resume();

    void End();

    bool IsIdle() const noexcept;
    bool IsRuning() const noexcept;
    bool IsDead() const noexcept;

   private:
    ERUNNING_STATE running = ERUNNING_STATE::RS_IDLE;
    std::unique_ptr<IPipelineFragmentHandler> handler;
};

}  // namespace Toy::Graphics
