#pragma once

#include "IPipeline.hpp"
#include "PipelineFragment.hpp"
#include <memory>
#include <unordered_set>

namespace Toy::Graphics
{
	class Pipeline final: public IPipeline
	{
	public:
		int Initialize() override;
		void Tick() override;

		void AddPipelineFragment(PipelineFragment* fg) override;

		
	private:
		void Finalize() override;
		void Render() override;
		void BeforeRender() override;
		void AfterRender() override;
		
		std::unordered_set<PipelineFragment*> custom_render_funcs;
	};
}