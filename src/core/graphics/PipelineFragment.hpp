#pragma once

#include "IObject.hpp"
#include "pch.hpp"
#include "IPipelineFragmentHandler.hpp"

namespace Toy::Graphics
{
	class  TOY_LIB_API PipelineFragment : public Toy::Engine::NoCopy
	{
	public:
		void Init(IPipelineFragmentHandler* handler);
		IPipelineFragmentHandler* GetHandler() const noexcept;
		void Stop();

		void Resume();

		void End();

		int GetState() const noexcept;

	private:
		int running = 0;
		IPipelineFragmentHandler* handler;
	};

}
