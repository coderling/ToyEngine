#pragma once

#include "IObject.hpp"
#include "pch.hpp"
#include "IPipelineFragmentHandler.hpp"

namespace Toy::Graphics
{
	enum class PIPELINE_STAGE
	{
		BEFORE_RENDER,
		ONRENDER,
		AFTER_RENDER
	};

	class  TOY_LIB_API PipelineFragment : public Toy::Engine::NoCopy
	{
	public:
		PipelineFragment(PIPELINE_STAGE stage);
		void Init(IPipelineFragmentHandler* handler);
		IPipelineFragmentHandler* GetHandler() const noexcept;
		void Stop();

		void Resume();

		void End();

		int GetState() const noexcept;
		PIPELINE_STAGE GetStage() const noexcept;

	private:
		int running = 0;
		IPipelineFragmentHandler* handler;
		PIPELINE_STAGE stage;
	};

}
