#pragma once

#include "ISystem.hpp"
#include "PipelineFragment.hpp"
#include <memory>

namespace Toy::Graphics
{
	class IPipeline : public Toy::Engine::ISystem
	{
	public:
		static IPipeline* GetInstance();
		virtual int Initialize() = 0;
		virtual void AddPipelineFragment(PipelineFragment* fg) = 0;
	protected:
		virtual void Render() = 0;
		virtual void BeforeRender() = 0;
		virtual void AfterRender() = 0;
	};
}