#pragma once

#include "../../interface/ISystem.hpp"

namespace Toy::Graphics
{
	class IPipeline : public Toy::Engine::ISystem
	{
	public:
		virtual int Initialize() = 0;
		virtual void Render() = 0;
		void Tick() override final { Render(); }
	};
}